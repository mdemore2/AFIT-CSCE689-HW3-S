//
// Created by mdemore2 on 2/5/20.
//
#include "PCalc_T.h"
#include <cmath>
#include <thread>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <future>
#include <chrono>

PCalc_T::PCalc_T(unsigned int array_size, unsigned int num_threads):PCalc(array_size)
{
    this->numthreads = num_threads;
}


void PCalc_T::markNonPrimes()
{
    this->at(0) = false;
    this->at(1) = false;

    threadProgress = std::vector<unsigned int>(numthreads,UINT32_MAX); //thread updates number it is currently processing
    threadRunning = std::vector<bool>(numthreads,false); //whether or not thread currently working on calcs
    newThreadVals = std::vector<unsigned int>(numthreads); //new value for thread to work on

    bool threadsAssigned = false;
    int threadID = -1;
    int spawnedThreads = 0;


    //this->at(0) = false;
    //this->at(1) = false;
    #pragma omp parallel
    for(unsigned int i  = 2; i < sqrt(this->array_size()); i++)
    {
        
        if(this->at(i))
        {
            unsigned int num = pow(i,2);
            while(num < this->array_size())
            {
                //markfalse at num position
                this->at(num) = false;
                num += i;
            }
        }
        
    }


    //old method commented out below
    /*for(unsigned int i  = 2; i < sqrt(this->array_size()); i++)
    {
        

        if(this->at(i))
        {
            //if current num to be threaded is >= minvalue being processed by any other thread, wait until passed this
            while(i >= minValWorking()){}

            while(threadID<0){threadID = threadAvailable();}
            //if no thread available, wait
           

            if(!threadsAssigned)
            {

                auto f = [=](int i, int threadID){threadFunction(i,threadID);};
                //lambda of work to give to thread
              
                threadRunning[threadID] = true;
                threadProgress[threadID] = i;
                newThreadVals[threadID] = i;
                //update global vals
                
                std::thread newThread(f, i,threadID);
                threads.push_back(std::move(newThread));
                //create and store thread

                //track number of threads created
                spawnedThreads++;

                if(spawnedThreads == numthreads)
                {
                    threadsAssigned = true;
                }
                    

            }
            else
            {   
                //give new value to thread
                newThreadVals[threadID] = i;
                threadProgress[threadID] = i;
                threadRunning[threadID] = true;
                    
            }

        }
         
    }

    //kill threads
    mainDone = true;
    finishThreads();*/

}

//marknonprime function to give to threads
void PCalc_T::threadFunction(unsigned int i, int threadID)
{
    
    unsigned int num = pow(i,2);
    while(num < this->array_size())
    {
        //markfalse at num position
        this->at(num) = false;
        num += i;
        threadProgress[threadID] = num;
    }
        
    
    //let main thread know ready for new value
    threadRunning[threadID] = false;
    threadProgress[threadID] = UINT32_MAX;

    //wait for new val from main thread or until program end
    while(newThreadVals.at(threadID) == i){
        if(mainDone)
        {
            i = 0;
        }
    }

    if(!mainDone){
        threadFunction(newThreadVals.at(threadID),threadID);
    }
    

}

//return lowest number currently being worked on by all threads
int PCalc_T::minValWorking()
{
    unsigned int minval = UINT32_MAX,val = 0;

    for(unsigned int i = 0; i < numthreads; i++)
    {
        val = threadProgress.at(i);
        if(val < minval)
        {
            minval = val;
        }

    }
    return minval;

}

//return which thread is ready for next value
int PCalc_T::threadAvailable()
{

    for(int i = 0; i < numthreads; i++)
    {
        if(!threadRunning.at(i))
        {
            return i;
        }
    }
    return -1;

}


//join all threads once calculation complete
void PCalc_T::finishThreads()
{
    for(int i = 0; i < threads.size(); i++)
    {
        
        if(threads.at(i).joinable())
        {
            //std::cout <<"Waiting for thread " << i <<" to complete\n";
            threads.at(i).join();
        }
        
    }
}