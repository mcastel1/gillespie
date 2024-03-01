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
//#include <stdint.h>

#include "gsl_rng.h"
#include "gsl_math.h"
#include "gsl_sf_log.h"
#include "gsl_randist.h"

/*compile on mac
 //compile without optimization
 g++ main.cpp -llapack -lgsl -lcblas -lm -O0 -Wno-deprecated -I ./ -I/usr/local/include/gsl/ -o main.o -Wall -DHAVE_INLINE
 
 //compile with optimization
 g++ main.cpp -llapack -lgsl -lcblas -lm -O3 -Wno-deprecated -I ./ -I/usr/local/include/gsl/ -o main.o -Wall -DHAVE_INLINE
 
 ./main.o -N 1 -s 0 -S 1024
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
    unsigned long long int/*, N=0*/ S=0, s;
    unsigned int i, seed=0;
    clock_t start=0, end=0;
    
    cout.precision(cout_precision);
    BitSet_one.ResizeAndSetAll(1);
    for(i = 0; i<n_bits; i++){
        Bits_one.Set(i, true);
        Bits_zero.Set(i, false);
    }
    
    
    while ((options = getopt(argc, argv, ":S:s:")) != -1) {
        
        switch (options) {
                
                //                case 'N':
                //                    N = ((unsigned int)atoi(optarg));
                //                    break;
                
            case 's':
                seed = ((unsigned int)atoi(optarg));
                break;
                
            case 'S':
                S = ((unsigned int)gsl_pow_int(10, atoi(optarg)));
                break;
                
                
        }
        
    }
    

    
    //    TestUnsignedIntMultiply(S, seed);
    //    SpeedTestUnsignedIntMultiply(128, S, seed);
    //    TestUnsignedIntAddTo(S, seed);
    //    TestDoubleAddTo(S, seed);
    //    SpeedTestDoubleAddTo(S, seed);
    //    SpeedTestUnsignedIntAddto(128, S, seed);
        TestFractionFloorMultiply(S, seed);
    //    SpeedTestFractionFloorMultiply(128, S, seed);
    
    
    
    /*
    System Frank(128, seed);
    
    start = clock();
    for(s=0; s<S; ++s){
        Frank.Iterate();
    }
    end = clock();
    cout << "Time for S Iterate()s with bits = " << std::scientific << ((double)(end - start))/CLOCKS_PER_SEC << "s" <<  endl << endl;
   
    
    cout << endl << "dummy print";
    Frank.Z.PrintBase10("");
    Frank.RHS.PrintBase10("");
     */
    
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
