//
// Created by mdemore2 on 2/5/20.
//
#include "PCalc_T.h"
#include <cmath>

PCalc_T::PCalc_T(unsigned int array_size, unsigned int num_threads):PCalc(array_size)
{
    //PCalc::PCalc(array_size);
    this->num_threads = num_threads;
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
    for(int i  = 2; i < sqrt(this->array_size()); i++)
    {
        
        if(this->at(i))
        {
            int num = pow(i,2);
            while(num < this->array_size())
            {
                //markfalse at num position
                this->at(num) = false;
                num += i;
            }
        }
        
    }

}