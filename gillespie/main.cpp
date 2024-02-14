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
    
    int options;
    unsigned int seed=0, N=0, S=0;
    
    while ((options = getopt(argc, argv, ":N:s:S:")) != -1) {
        
        switch (options) {
                
            case 'N':
                N = ((unsigned int)atoi(optarg));
                break;
                
            case 's':
                seed = ((unsigned int)atoi(optarg));
                break;
                
            case 'S':
                S = ((unsigned int)atoi(optarg));
                break;
                
                
        }
        
    }
    
    BitSet b(gsl_pow_int(2, 20));
    UnsignedInt e(4);
    b.SetRandom((int)0);
    e.SetRandom((int)2);
    
    cout << "Before" << endl;
    cout << "b:" << endl;
    b.Print();
    cout << "e:" << endl;
    e.Print();
    
    b >>= (&e);
    
    cout << "After" << endl;
    cout << "b:" << endl;
    b.Print();
    cout << "e:" << endl;
    e.Print();

    

    
    //
    //    Double a;
    //    a.SetRandom((int)0);
    //    a.Print();
    //    a.PrintBase10_IEEE754();
    //
    
    //     System sys(N, seed);
    
    
    /*
     //some tests for UnsignedInt class
    clock_t start=0, end=0;
    unsigned int s;
    
    
    
    
    vector<UnsignedInt> A(S), B(S);
    vector<unsigned long long int> a(S), b(S);
    gsl_rng* ran;
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    gsl_rng_set(ran, seed);
    
    
    
    for(s=0; s<S; s++){
        A[s] = UnsignedInt(8);
        B[s] = UnsignedInt(4);
        (A[s]).SetRandom(s);
        (B[s]).SetRandom(s+1);
        (A[s]).Resize(A[s].GetSize()+1);
    }
    
    start = clock();
    for(s=0; s<S; s++){
        
        A[s].PrintBase10_IEEE754();
        B[s].PrintBase10_IEEE754();
        
        A[s]-=(B[s]);
        
        A[s].PrintBase10_IEEE754();
        
    }
    end = clock();
    
    cout << "Time with bits = " << end - start << "\n";
    
    
    
    for(s=0; s<S; s++){
        a[s] = gsl_rng_uniform_int(ran, 9);
        b[s] = gsl_rng_uniform_int(ran, 9);
    }
    start = clock();
    for(s=0; s<S; s++){
        a[s]+=b[s];
    }
    end = clock();
    cout << "Time without bits = " << end - start << "\n";
    */

    
    
    //some tests for Double class
    /*
    Double a;
//    a.SetRandom((int)0);
    a.SetAllVertically_IEEE754(32.42354);
    a.Print();
    a.PrintBase10_IEEE754();
    */
//    bitwise_print_double(-.3423589247);
     
    
    return 0;
    
}
