//
//  double.cpp
//  gillespie
//
//  Created by Michele on 10/02/2024.
//

#include "double.hpp"

//default constructor
inline Double::Double(void){
    
    b.resize(54);
    e.resize(11);
    
}

//set the fraction to zero, the exponent to 1023 and the sign to +
inline void Double::Clear(){
    
    unsigned int p;
    
    //set the fraction to zero
    for(p=0; p<b.size(); p++){
        (b[p]).n = 0;
    }
    
    //set the exponent to 1023
    for(p=0; p<e.size()-1; p++){
        (e[p]).SetAll(true);
    }
    e.back().SetAll(false);
    
    //set the sign to +
    s.SetAll(false);
    
}


//initialize *this randomly with seed seed
inline void Double::SetRandom(unsigned int seed){
    
    unsigned int i;
    gsl_rng* ran;
    
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    gsl_rng_set(ran, seed);
    
    
    for(i=0; i<b.size(); i++){
        b[i].SetRandom(ran);
    }
    for(i=0; i<e.size(); i++){
        e[i].SetRandom(ran);
    }
    s = (bool)gsl_rng_uniform_int(ran, 2);
    
    gsl_rng_free(ran);

    
}

