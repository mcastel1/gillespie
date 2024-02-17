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
 */


#include "main.hpp"
#include "lib.cpp"
#include "bits.cpp"
#include "bitset.cpp"
#include "unsigned_int.cpp"
#include "double.cpp"
#include "system.cpp"


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
    
    cout.precision(cout_precision);
    
        int options;
        unsigned int seed=0/*, N=0, S=0*/;
    
        while ((options = getopt(argc, argv, ":s:")) != -1) {
    
            switch (options) {
    
//                case 'N':
//                    N = ((unsigned int)atoi(optarg));
//                    break;
    
                case 's':
                    seed = ((unsigned int)atoi(optarg));
                    break;
    
//                case 'S':
//                    S = ((unsigned int)atoi(optarg));
//                    break;
    
    
            }
    
        }
    //
    //
    
    //
    //    UnsignedInt n;
    //    n.Resize(n_bits_mantissa);
    //    n.SetRandom((unsigned int)0);
    //    n.SetAllFromDouble(0.15349687467);
    ////    n.SetFromDouble(2, 0.94637);
    //    n.Print();
    //
    
    
    
    //    some tests for Double class
    //
    Double a, b;
    double error;
    vector<double> v_a, v_b, v_a_plus_b;
    unsigned int i;
    gsl_rng* ran;
    
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    gsl_rng_set(ran, seed);

        
    for(i=0; i<n_bits; i++){
        a.Set(i, false, 1023 + (128/2 - gsl_rng_uniform_int(ran, 128)), gsl_rng_uniform(ran));
        b.Set(i, false, 1023 + (128/2 - gsl_rng_uniform_int(ran, 128)), gsl_rng_uniform(ran));
    }
        

//    cout << "----------- Before += -----------" << endl;
//    cout << "a : " << endl;
//    a.Print();
//    a.PrintBase10();

//    cout << "b : " << endl;
//    b.Print();
//    b.PrintBase10();
    
    a.GetBase10(v_a);
    b.GetBase10(v_b);

    a+=b;
    
//    cout << "----------- After += -----------" << endl;
//    cout << "a+b: " << endl;
//    a.Print();
//    a.PrintBase10();
    
    a.GetBase10(v_a_plus_b);
    
    cout << "Check of the result:" << endl;
    for(error = 0.0, i=0; i<n_bits; ++i){
        if(fabs(((v_a[n_bits-1-i]+v_b[n_bits-1-i])-v_a_plus_b[n_bits-1-i])/v_a_plus_b[n_bits-1-i]) > error){error = fabs(((v_a[n_bits-1-i]+v_b[n_bits-1-i])-v_a_plus_b[n_bits-1-i])/v_a_plus_b[n_bits-1-i]);}
        
        cout << "[" << n_bits-1-i << "]:\t\t\t" << v_a[n_bits-1-i]+v_b[n_bits-1-i] << "\t\t\t" << v_a_plus_b[n_bits-1-i] << "\t\t\t" << fabs(((v_a[n_bits-1-i]+v_b[n_bits-1-i])-v_a_plus_b[n_bits-1-i])/v_a_plus_b[n_bits-1-i]) << endl;
    }
    cout << "Maximum relative error = " << error << endl;
    //
    
    
    cout << endl;
    return 0;
    
}
