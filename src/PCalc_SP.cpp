//
// Created by mdemore2 on 2/5/20.
//
#include "PCalc_SP.h"
#include <cmath>

PCalc_SP::PCalc_SP(unsigned int array_size):PCalc(array_size)
{
    //PCalc::PCalc(array_size);
}
/*
PCalc_SP::~PCalc_SP()
{
    PCalc::~PCalc();
}*/

void PCalc_SP::markNonPrimes()
{
    this->at(0) = false;
    this->at(1) = false;
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

}