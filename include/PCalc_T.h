#ifndef PCALC_T_H
#define PCALC_T_H

#include "PCalc.h"
#include <vector>
#include <thread>

// Your implementation of PCalc_T class should go here. 
// Make sure your constructor takes in two parameters:

// PCalc_T::PCalc_T(unsigned int array_size, unsigned int num_threads);

// Call the parent constructor when initializing your constructor and pass in array_size. Then
// use num_threads to cap off how many threads you use to calculate all prime numbers

class PCalc_T : public PCalc
{
    public:

        PCalc_T(unsigned int array_size, unsigned int num_threads);

        //virtual ~PCalc();

        // Overload me!
        void markNonPrimes();

        void threadFunction(int i, int threadID);

        //void printPrimes(const char *filename);

        // Retrieve the prime boolean element at x
        //bool &operator [] (unsigned int x);
        //bool &at(unsigned int x);

        //unsigned int array_size() { return asize; };
        unsigned int num_threads() { return numthreads; };
        int minValWorking();
        bool threadAvailable();

        // if you overload, don't forget to call me
        //virtual void cleanup();

    protected:

        // Do not forget, your constructor should call this constructor
        //PCalc(unsigned int array_size);

    private:

        //PCalc() {};

        // Stuff to be left alone
        //unsigned int asize;
        //bool *primelist;
        unsigned int numthreads;

        std::vector<std::thread> threads; 
        std::vector<int> threadProgress;  //thread updates number it is currently processing
        std::vector<bool> threadRunning;
};

#endif
