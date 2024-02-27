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

#include "gsl_rng.h"
#include "gsl_math.h"
#include "gsl_sf_log.h"

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
    unsigned long long int seed=0/*, N=0*/, S=0;
    unsigned int i;
    
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
    SpeedTestUnsignedIntAddto(128, S, seed);
    //    TestFractionFloorMultiply(S, seed);
    //    SpeedTestFractionFloorMultiply(128, S, seed);
    
        
    
    cout << endl;
    return 0;
    
}
