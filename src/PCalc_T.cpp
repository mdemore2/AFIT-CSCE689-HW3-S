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
    threadProgress = std::vector<int>(numthreads,3); //thread updates number it is currently processing
    threadRunning = std::vector<bool>(numthreads,false);

    //std::vector<std::thread>::iterator itThreads = threads.begin();
    //std::vector<int>::iterator itThreadProgress = threadProgress.begin();


    for(int i  = 2; i < sqrt(this->array_size()); i++)
    {
        if(this->at(i))
        {
            //if current num to be threaded is >= minvalue being processed by any other thread, wait until passed this
            while(i >= minValWorking()){}

            while(!threadAvailable()){}
            //if no thread available, wait

            for(int threadID = 0; threadID < numthreads; threadID++)
            {
                //otherwise a thread is open, give value to thread
                if(!threadRunning.at(threadID))
                {
                    auto f = [this](int i, int threadID){threadFunction(i,threadID);};
                    std::thread newThread(f, i,threadID);
                    threads.push_back(std::move(newThread));
                    threadRunning[threadID] = true;
                    threadProgress[threadID] = i;
                }


            }

        }
         
    }
    for(int i = 0; i < threads.size(); i++)
    {
        
        if(threads.at(i).joinable())
        {
            threads.at(i).join();
        }
        
    }

}


void PCalc_T::threadFunction(int i, int threadID)
{
    if(i < sqrt(this->array_size()))
    {
        if(this->at(i))
        {
            int num = pow(i,2);
            while(num < this->array_size())
            {
                //markfalse at num position
                this->at(num) = false;
                num += i;
                threadProgress.at(threadID) = num;
            }
        }
    }

    threadRunning.at(threadID) = false;

}

int PCalc_T::minValWorking()
{
    //std::vector<int>::iterator itThreadProgress = threadProgress.begin();
    int minval = INFINITY,val = 0;

    for(int i = 0; i < threadProgress.size(); i++)
    {
        val = threadProgress.at(i);
        if(val < minval)
        {
            minval = val;
        }

    }
    return minval;

}

bool PCalc_T::threadAvailable()
{
    //std::vector<bool>::iterator itThreadRunning = threadRunning.begin();

    for(int i = 0; i < threadRunning.size(); i++)
    {
        if(!threadRunning.at(i))
        {
            return true;
        }
    }
    return false;

}