//
//  main.h
//  gillespie
//
//  Created by Michele on 07/02/2024.
//

#define n_bits 64
#define n_bits_mantissa 52
#define n_bits_exponent 11
#define n_bits_sign 1
//number of bits to write the random number (Fraction) R for the Gillespie simulation
#define n_bits_R 12
//the maximum value for c[j]
#define M 8
#define cout_precision 8
const unsigned long long int ullong_1 = 1;
const unsigned long long int ullong_0 = 0;

using namespace std;


class UnsignedInt;
#include "bits.hpp"
#include "bitset.hpp"

//fill all the entries of BitSet_one and of Bits_one with 1, same for 0 with Bits_zero
BitSet BitSet_one;
Bits Bits_one, Bits_zero;


