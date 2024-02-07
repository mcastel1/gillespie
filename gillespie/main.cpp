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
#include "gsl_sf_pow_int.h"
#include "main.h"

using namespace std;

inline unsigned long long int two_pow(unsigned long long int i){
    
    return ((unsigned long long int)gsl_sf_pow_int(2.0, ((int)i)));
    
}

//return the number of bits necessary to write n in base 2
unsigned int inline bits(unsigned long long int n){
    
    unsigned int s;
    
    for(s=0; two_pow(s) <= (unsigned long long int)n; s++){}
    
    return s;
    
}





Int::Int(unsigned long long int N){
    
    b.resize(bits(N));
    
}


System::System(void){
    
}


System::System(unsigned int N_in, unsigned int seed_in){
    
    unsigned int i;
    
    ran = gsl_rng_alloc(gsl_rng_gfsr4);

    N = N_in;
    seed = seed_in;

    for(x.clear(), i=0; i<3; ++i){
        x.push_back(Int(N));
    }
    
    gsl_rng_set(ran, seed);
    
}

void System::iterate(void){
    
    
    
}



int main(int argc, char * argv[]) {
    
    int options;
    unsigned int seed=0, N=0;
    

    while ((options = getopt(argc, argv, ":N:s:")) != -1) {
         
         switch (options) {
                 
             case 'N':
                 N = ((unsigned int)atoi(optarg));
                 break;
                 
             case 's':
                 seed = ((unsigned int)atoi(optarg));
                 break;
                 
         }
         
     }
     
    System sys(N, seed);

   
    return 0;
    
}
