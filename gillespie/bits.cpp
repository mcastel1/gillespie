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


//set the s-th bit of *this equal to bit
void Bits::Set(unsigned int s, bool bit){
    
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




//set all n_bits entries of *this equal to *bit
void Bits::SetAll(bool bit){
    
    for(unsigned int s=0; s<n_bits; s++){
        this->Set(s, bit);
    }
    
}


//return the s-th bit ofinput
bool Bits::Get(unsigned int s){
    
    return ((n >> s) & ullong_1);
    
}


//set *this randomly with seed seed
void Bits::SetRandom(unsigned int seed){
    
    gsl_rng* ran;
    
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    gsl_rng_set(ran, seed);

    SetRandom(ran);
    
    gsl_rng_free(ran);

}

//set *this randomly with random number generator ran
void Bits::SetRandom(gsl_rng* ran){
    
    unsigned int s;
    
    for(s=0; s<n_bits; s++){
        Set(s, (bool)(gsl_rng_uniform_int(ran, 2)));
    }
    
}


//return the one's complement of *this 
Bits Bits::Complement(void){
    
    Bits result;
    
    for(unsigned int s=0; s<n_bits; s++){
        result.Set(s, 1-(this->Get(s)));
    }
    
    return result;
    
}


//set all bits of *this to 0
void Bits::Clear(void){
    
    n = 0;
    
}

void Bits::Print(void){
    
    cout << "{ ";
    for(unsigned int s=0; s<n_bits; s++){
        cout << this->Get(n_bits-1-s);
    }
    cout << " }\n";
    
}


//return (this->n) | (m.n) (bitwise OR)
inline Bits Bits::operator | (const Bits& m){
    
    return Bits((n | (m.n)));
    
}


//return (this->n) & (m.n) (bitwise AND)
inline Bits Bits::operator & (const Bits& m){
    
    return Bits((n & (m.n)));
    
}


//return (this->n) ^ (m.n) (bitwise xOR)
inline Bits Bits::operator ^ (const Bits& m){
    
    return Bits((n ^ (m.n)));
    
}


inline Bits operator ~ (const Bits& m){
    
    return Bits((~(m.n)));
    
}
