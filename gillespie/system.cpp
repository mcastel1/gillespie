//
//  system.cpp
//  gillespie
//
//  Created by Michele on 07/02/2024.
//

#include "system.hpp"

System::System(void){
    
}

System::System(unsigned long long int N_in, unsigned int seed_in){
    
    unsigned int i, s, *n;
    const double p[] = {1.0, 1.0, 2.0};


    n = new unsigned int [3];
    ran = gsl_rng_alloc(gsl_rng_gfsr4);

    N = N_in;
    seed = seed_in;

    for(x.clear(), c.clear(), i=0; i<3; ++i){
        
        x.push_back(UnsignedInt(N));
        c.push_back(UnsignedInt(n_bits_N));
        
    }
    
    
        
    for(s=0; s<n_bits; s++){
        
        //draw the initial number of particles of the three species according to a multinomial distribution
        gsl_ran_multinomial(ran, 3, (unsigned int)N, p, n);

        for(i=0; i<3; ++i){
            
            //write the initial number of particles in x
            x[i].Set(s, n[i]);
            //draw the values of c and write them in c
            c[i].Set(s, gsl_rng_uniform_int(ran, pow(2, n_bits_N)));
            
        }
        
    }
    
    for(i=0; i<3; ++i){
        
        cout << "c[" << i << "]" << endl;
        c[i].PrintBase10("");
        
   
        
    }
    
    
    for(i=0; i<3; ++i){
        
        cout << "x[" << i << "]" << endl;
        x[i].PrintBase10("");
        
    }
    
    gsl_rng_set(ran, seed);
    delete [] n;
    
}

void System::Iterate(void){
    
    
    
}
