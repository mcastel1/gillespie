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

using namespace std;

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
    
    System sys;
    
    
    
    
    while ((options = getopt(argc, argv, ":Ss:")) != -1) {
         
         switch (options) {
                 
             case 's':
                 (sys.seed) = (long)atoi(optarg);
                 break;
                 
         }
         
     }
    
    
    
    return 0;
    
}
