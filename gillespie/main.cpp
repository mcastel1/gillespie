#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <fstream>
#include <strstream>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <list>
#include <stdio.h>
#include <time.h>
#include <getopt.h>
//this has to be uncommented to run on mesopsl
#include <stdint.h>

#include "gsl_rng.h"
#include "gsl_math.h"
#include "gsl_sf_log.h"
#include "gsl_randist.h"

/*compile on mac
 //compile without optimization
 g++ main.cpp -llapack -lgsl -lcblas -lm -O0 -Wno-deprecated -I ./ -I/usr/local/include/gsl/ -o main.o -Wall -DHAVE_INLINE
 
 //compile with optimization
 g++ main.cpp -llapack -lgsl -lcblas -lm -O3 -Wno-deprecated -I ./ -I/usr/local/include/gsl/ -o main.o -Wall -DHAVE_INLINE
 clear; g++ main.cpp -llapack -lgsl -lcblas -lm -O3 -Wno-deprecated -I ./ -I/usr/local/include/gsl/ -o main.o -Wall -DHAVE_INLINE;  ./main.o -N 128 -S 5 -s 0 -o /Users/michele/Desktop

 //compile on calcsub
 g++ -O3 -o main.o -I ./ -lgsl -lgslcblas -lm main.cpp -Wall -I/usr/include/gsl
 
 ./main.o -N 128 -S 5 -s 0 -o /Users/michele/Desktop
 */

/*
 note: - the performance test is very different if you do it on Xcode or on command line with -O3
 - to circumvent the slow down with >>= in Double::AddTo, represent a Double as a BitSet, where the first bs represent the mantissa and the others the part > 1
 - make sure that Double::AddTo does not alter the content of *addend
 - if you run  void SpeedTestUnsignedIntAddTo and instead of calling once (A[s]).SubstractTo(&(B[s]), &carry) you call it twice, the execution time does not change and it stays smaller than the executio time without bits -> The gillespie simulation should be improved by the approach with bits
 */



#include "main.hpp"
#include "lib.cpp"
#include "bits.cpp"
#include "bitset.cpp"
#include "fraction.cpp"


#include "int.cpp"
#include "unsigned_int.cpp"
#include "double.cpp"
#include "system.cpp"

//all entries of BitSet_one are equal to 1


/*
 void UnsignedInt::SetRandom(unsigned long long int seed){
 
 int i;
 gsl_rng* ran;
 
 ran = gsl_rng_alloc(gsl_rng_gfsr4);
 gsl_rng_set(ran, seed);
 
 
 for(i=0; i<b.size(); i++){
 
 
 }
 
 }
 */



int main(int argc, char * argv[]) {
    
    int options;
    unsigned long long int N=0, S=0, s;
    unsigned int i, seed=0;
    string output_directory;
    clock_t start_nobits, start_bits, end_nobits, end_bits;
    
    cout.precision(cout_precision);
    BitSet_one.ResizeAndSetAll(1);
    for(i = 0; i<n_bits; i++){
        Bits_one.Set(i, true);
        Bits_zero.Set(i, false);
    }
    
    
    while ((options = getopt(argc, argv, ":N:S:s:o:")) != -1) {
        
        switch (options) {
                
            case 'N':
                N = ((unsigned int)atoi(optarg));
                break;

            case 'S':
                S = ((unsigned int)gsl_pow_int(10, atoi(optarg)));
                break;
                
            case 's':
                seed = ((unsigned int)atoi(optarg));
                break;
                
            case 'o':
                output_directory.assign(optarg);
                break;
                            
                
        }
        
    }
    
    
//    UnsignedInt I(24);
//    I.SetRandom((unsigned int)0);
//    I.PrintBase10("before");
//    I.DivideByTwoTo();
//    I.PrintBase10("after");

    
    
    //    TestUnsignedIntMultiply(S, seed);
    //    SpeedTestUnsignedIntMultiply(128, S, seed);
    //    TestUnsignedIntAddTo(S, seed);
    //    TestDoubleAddTo(S, seed);
    //    SpeedTestDoubleAddTo(S, seed);
    //    SpeedTestUnsignedIntAddto(128, S, seed);
    //        TestFractionFloorMultiply(S, seed);
    //        SpeedTestFractionFloorMultiply(32, 128, S, seed);
    
    
    
    //
    SystemBits FRANK(N, seed, output_directory);
    systemnobits frank(N, seed, output_directory);
    
    
    //********************* speed test without bits  *********************
    start_nobits = clock();
    for(s=0; s<n_bits*S; ++s){
        frank.iterate();
    }
    end_nobits = clock();
    frank.outfile.close();
    cout << endl << "Time for [n_bits*S] Iterate()s without bits = \t\t " << std::scientific << ((double)(end_nobits - start_nobits))/CLOCKS_PER_SEC << "s" <<  endl;

    
    
    //********************* speed test with bits  *********************
    start_bits = clock();
    for(s=0; s<S; ++s){
        FRANK.Iterate();
    }
    end_bits = clock();
    FRANK.outfile.close();
    cout << "Time for S Iterate()s with bits = \t\t         " << std::scientific << ((double)(end_bits - start_bits))/CLOCKS_PER_SEC << "s" <<  endl << endl;
    
    
    cout << "Gain bits/nobits = " << ((double)(end_nobits - start_nobits)) / ((double)(end_bits - start_bits)) << endl;
    
    cout << endl << "dummy print";
    FRANK.L.PrintBase10("");
    cout << FRANK.tau << frank.tau << frank.z << frank.rhs;
    //
    
    cout << endl;
    return 0;
    
    /*
     double x = gsl_rng_uniform(Frank.ran);
     Fraction R;
     vector<bool> v(n_bits_mantissa);
     R.Resize(n_bits_mantissa);
     R.Fraction::SetAllFromDoubleMantissa(x, &v);
     
     
     cout << "x:" << x << endl;
     R.Fraction::PrintBase10("R");
     */
    
}
