//
//  main.h
//  gillespie
//
//  Created by Michele on 07/02/2024.
//

#ifndef main_hpp
#define main_hpp

#include <iostream>

using namespace std;



#define n_bits 64
#define n_bits_mantissa 52
#define n_bits_exponent 11
#define n_bits_sign 1
//the maximum value for c[j]
#define M 8
#define cout_precision 8
const unsigned long long int ullong_1 = 1;
const unsigned long long int ullong_0 = 0;



class UnsignedInt;
#include "bits.hpp"
#include "bitset.hpp"

//fill all the entries of BitSet_one and of Bits_one with 1, same for 0 with Bits_zero
BitSet BitSet_one;
Bits Bits_one, Bits_zero;


#endif
