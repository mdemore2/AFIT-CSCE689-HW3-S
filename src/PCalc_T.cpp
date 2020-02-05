//
// Created by mdemore2 on 2/5/20.
//
#include "PCalc_T.h"
#include <cmath>
#include <thread>
#include <stdlib.h>
#include <vector>

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

    std::vector<std::thread> threadList = std::vector<std::thread>(numthreads);
    std::vector<int> threadProgress = std::vector<int>(numthreads,3); //thread updates number it is currently processing

    std::vector<std::thread>::iterator itThreadList = threadList.begin();
    std::vector<int>::iterator itThreadProgress = threadProgress.begin();


    for(int i  = 2; i < sqrt(this->array_size()); i++)
    {
        if(this->at(i))
        {
            //if current num to be threaded is <= minvalue being processed by any other thread, wait until passed this
            while(i <= minValWorking()){}
            int threadID = 0;
            for(itThreadList = threadList.begin(); itThreadList != threadList.end(); itThreadList++)
            {
                //if no thread available, wait
                //otherwise a thread is open, give value to thread

                threadID++;
            }

        }
         
    }

}
void PCalc_T::threadFunction(int i, int threadID)
{
    while(i < sqrt(this->array_size()))
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

}

int PCalc_T::minValWorking()
{
    std::vector<int>::iterator itThreadProgress = threadProgress.begin();
    int minval = INFINITY,val = 0;

    for(itThreadProgress = threadProgress.begin();itThreadProgress != threadProgress.end();itThreadProgress++)
    {
        val = *itThreadProgress;
        if(val < minval)
        {
            minval = val;
        }

    }
    return minval;

}