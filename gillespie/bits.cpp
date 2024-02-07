//
//  bits.cpp
//  gillespie
//
//  Created by Michele on 07/02/2024.
//

#include "bits.hpp"

Bits::Bits(){}

Bits::Bits(unsigned long long int n_in){
    
    n  = n_in;
    
}


//set the i-th entry of input equal to bit
void Bits::SetBit(unsigned int s, bool bit){
    
    unsigned int p;
    unsigned long long int result;
    
    result = 0;
    for(p=0; p<n_bits; p++){
        
        if(p!=s){
            
            result |= (((n >> p) & ullong_1) << p);
            
        }else{
            
            if(bit){
                result |= (ullong_1 << s);
            }
            
        }
        
    }
    
    n = result;
    
}

//return the s-th bit ofinput
bool Bits::GetBit(unsigned int s){
    
    return ((n >> s) & ullong_1);
    
}


//set *this randomly with seed seed
void Bits::SetRandom(unsigned int seed){
    
    unsigned int s;
    gsl_rng* ran;
    
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    gsl_rng_set(ran, seed);

    for(s=0; s<n_bits; s++){
        SetBit(s, (bool)(gsl_rng_uniform_int(ran, 2)));
    }
    
    gsl_rng_free(ran);

}


void Bits::Print(void){
    
    cout << "{ ";
    for(unsigned int s=0; s<n_bits; s++){
        cout << this->GetBit(n_bits-1-s);
    }
    cout << " }\n";
    
}
