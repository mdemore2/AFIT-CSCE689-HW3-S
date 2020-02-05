#ifndef PCALC_SP_H
#define PCALC_SP_H

#include "PCalc.h"

// Add your PCalc_SP class definition here as a child class of PCalc
// Be sure to overload the right methods from PCalc or it won't compile

// This class should manage the single process implementation of the prime number generator. I'd recommend
// getting this working first, then tackling multithreaded

class PCalc_SP : public PCalc
{
    public:
        PCalc_SP(unsigned int array_size);
        //~PCalc_SP();

        // Overload me!
        void markNonPrimes();

        //void printPrimes(const char *filename);

        // Retrieve the prime boolean element at x
        //bool &operator [] (unsigned int x);
        //bool &at(unsigned int x);

        //unsigned int array_size() { return asize; };

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
};

#endif
