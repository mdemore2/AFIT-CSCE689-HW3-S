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
    //PCalc::PCalc(array_size);
    this->numthreads = num_threads;
}
/*
PCalc_SP::~PCalc_SP()
{
    PCalc::~PCalc();
}*/

void PCalc_T::markNonPrimes()
{
    this->at(0) = false;
    this->at(1) = false;

    threads = std::vector<std::thread>(numthreads);
    threadProgress = std::vector<int>(numthreads,INFINITY); //thread updates number it is currently processing
    threadRunning = std::vector<bool>(numthreads,false);
    newThreadVals = std::vector<int>(numthreads);

    bool threadsAssigned = false;
    int threadID = -1;
    int spawnedThreads = 0;

    //std::vector<std::thread>::iterator itThreads = threads.begin();
    //std::vector<int>::iterator itThreadProgress = threadProgress.begin();


    for(int i  = 2; i < sqrt(this->array_size()); i++)
    {
        if(this->at(i))
        {
            //if current num to be threaded is >= minvalue being processed by any other thread, wait until passed this
            //std::cout<<"waiting for minval\n";
            while(i >= minValWorking()){}

            //std::cout<<"waiting for thread\n";
            while(threadID<0){threadID = threadAvailable();}
            //if no thread available, wait
            //std::cout<<"no longer waiting\n";

            if(!threadsAssigned)
            {

                //std::cout <<"making new thread\n";
                auto f = [=](int i, int threadID){threadFunction(i,threadID);};
                //auto future = std::async([this](int i, int threadID){threadFunction(i,threadID);},i,threadID);
                std::thread newThread(f, i,threadID);
                threads.push_back(std::move(newThread));
                threadRunning[threadID] = true;
                threadProgress[threadID] = i;
                newThreadVals[threadID] = i;

                spawnedThreads++;

                if(spawnedThreads == numthreads)
                {
                    threadsAssigned = true;
                    //std::cout << "max threads assigned\n";
                }
                    

            }
            else
            {   
                //while(!threadAvailable()){}

                //std::cout<<"assigning new value\n";
                //for(int threadIT = 0; threadIT < numthreads; threadIT++)
                
                    //if(!threadRunning.at(threadIT))
                    
                        //std::cout <<"new value assigned";
                newThreadVals[threadID] = i;
                threadProgress[threadID] = i;
                threadRunning[threadID] = true;
                //std::cout<<"new val assigned\n";
                    
                
            }

        }
         
    }

    mainDone = true;

    for(int i = 0; i < threads.size(); i++)
    {
        
        if(threads.at(i).joinable())
        {
            //std::cout <<"Waiting for thread " << i <<" to complete\n";
            threads.at(i).join();
        }
        
    }

}


void PCalc_T::threadFunction(int i, int threadID)
{
    //if(i < sqrt(this->array_size()))
    
        //if(this->at(i))
        
            int num = pow(i,2);
            while(num < this->array_size())
            {
                //markfalse at num position
                this->at(num) = false;
                num += i;
                threadProgress[threadID] = num;
            }
        
    

    threadRunning[threadID] = false;
    threadProgress[threadID] = INFINITY;
    while(newThreadVals.at(threadID) == i){
        if(mainDone)
        {
            i = 0;
        }
    }
    //std::cout<<"recieved new val";
    if(!mainDone){
        //std::cout<<"newvalrecieved/n";
        threadFunction(newThreadVals.at(threadID),threadID);}
    

}

int PCalc_T::minValWorking()
{
    //std::vector<int>::iterator itThreadProgress = threadProgress.begin();
    int minval = INFINITY,val = 0;

    for(int i = 0; i < numthreads; i++)
    {
        val = threadProgress.at(i);
        if(val < minval)
        {
            minval = val;
        }

    }
    return minval;

}

int PCalc_T::threadAvailable()
{
    //std::vector<bool>::iterator itThreadRunning = threadRunning.begin();

    for(int i = 0; i < numthreads; i++)
    {
        if(!threadRunning.at(i))
        {
            return i;
        }
    }
    return -1;

}