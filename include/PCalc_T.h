#ifndef PCALC_T_H
#define PCALC_T_H

#include "PCalc.h"
#include <vector>
#include <thread>
#include <omp.h>

// Your implementation of PCalc_T class should go here. 
// Make sure your constructor takes in two parameters:

// PCalc_T::PCalc_T(unsigned int array_size, unsigned int num_threads);

// Call the parent constructor when initializing your constructor and pass in array_size. Then
// use num_threads to cap off how many threads you use to calculate all prime numbers

class PCalc_T : public PCalc
{
    public:

        PCalc_T(unsigned int array_size, unsigned int num_threads);

        // Overload me!
        void markNonPrimes();

        void threadFunction(unsigned int i, int threadID);

        unsigned int num_threads() { return numthreads; };
        int minValWorking();
        int threadAvailable();
        void finishThreads();


    protected:

    private:

        
        unsigned int numthreads;

        std::vector<std::thread> threads; 
        std::vector<unsigned int> threadProgress;  //thread updates number it is currently processing
        std::vector<bool> threadRunning;
        std::vector<unsigned int> newThreadVals;
        bool mainDone = false;
};

#endif
