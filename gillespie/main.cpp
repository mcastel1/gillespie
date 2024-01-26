//
//  main.cpp
//  gillespie
//
//  Created by Michele on 25/01/2024.
//

#include <iostream>

#include "gsl_rng.h"

using namespace std;

class System{
    
public:
    
    long n_species, n_reactions, seed;
    vector<long> x;
    gsl_rng* ran;
    
    System(long, long, long);
    void iterate(void);
    

};

System::System(long n_species_in, long n_reactions_in, long seed_in){
    
    n_species = n_species_in;
    n_reactions = n_reactions_in;
    seed = seed_in;

    x.resize(n_species);
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    gsl_rng_set(ran, seed);

    
}

void System::iterate(void){
    
    
    
}



int main(int argc, const char * argv[]) {
    
    int options;
    long S, R, s;
    
    
    while ((options = getopt(argc, argv, ":S:R:s:")) != -1) {
         
         switch (options) {
                 
             case 'S':
                 S = (long)atoi(optarg);
                 break;
                 
             case 'R':
                 R = strtod(optarg,argv);
                 break;
                 
             case 's':
                 s = strtod(optarg,argv);
                 break;
                 
        
                 
         }
         
     }
    
    
    
    return 0;
    
}
