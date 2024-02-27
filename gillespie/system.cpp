//
//  system.cpp
//  gillespie
//
//  Created by Michele on 07/02/2024.
//

#include "system.hpp"

System::System(void){
    
}

System::System(unsigned int N_in, unsigned int seed_in){
    
    unsigned int i, s;
    
    ran = gsl_rng_alloc(gsl_rng_gfsr4);

    N = N_in;
    seed = seed_in;

    for(x.clear(), c.clear(), i=0; i<3; ++i){
        
        x.push_back(UnsignedInt(N));
        
        c.push_back(UnsignedInt(n_bits_N));
        for(s=0; s<n_bits; s++){
            c[i].Set(s, gsl_rng_uniform_int(ran, pow(2, n_bits_N)));
        }
        
    }
    
    gsl_rng_set(ran, seed);
    
}

void System::Iterate(void){
    
    
    
}
