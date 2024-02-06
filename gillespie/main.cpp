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

using namespace std;

inline unsigned long long int two_pow(unsigned long long int i){
    
    return ((unsigned long long int)gsl_sf_pow_int(2.0, ((int)i)));
    
}

//return the number of bits necessary to write n in base 2
unsigned int inline bits(unsigned int n){
    
    unsigned int s;
    
    for(s=0; two_pow(s) <= (unsigned long long int)n; s++){}
    
    return s;
    
}

class System{
    
public:
    
    long seed;
    vector<unsigned long long int> x;
    gsl_rng* ran;
    
    System(void);
    System(long);
    void iterate(void);
    

};

System::System(void){
    
  
    
}


System::System(long seed_in){
    
    seed = seed_in;

    x.resize(3);
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    gsl_rng_set(ran, seed);

    
}

void System::iterate(void){
    
    
    
}



int main(int argc, char * argv[]) {
    
    int options;
    long s=0;
    

    while ((options = getopt(argc, argv, ":s:")) != -1) {
         
         switch (options) {
                 
             case 's':
                 s = (long)atoi(optarg);
                 break;
                 
         }
         
     }
     
    System sys(s);

   
    return 0;
    
}
