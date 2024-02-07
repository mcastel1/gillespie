//
//  int.cpp
//  gillespie
//
//  Created by Michele on 07/02/2024.
//

#include "int.hpp"




Int::Int(void){
        
}

Int::Int(unsigned long long int N){
    
    b.resize(bits(N));
    
}


//initialize *this randomly
void Int::SetRandom(unsigned int seed){
    
    unsigned int s, p;
    gsl_rng* ran;
    
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    gsl_rng_set(ran, seed);


    for(s=0; s<b.size(); s++){
        for(p=0; p<n_bits; p++){
            b[s].SetBit(p, (bool)(gsl_rng_uniform_int(ran, 2)));
        }
    }
    
    gsl_rng_free(ran);

    
}


void Int::Print(void){
    
    unsigned int s;
    
    cout << "Int:\n";
    for(s=0; s<b.size(); s++){
        cout << "b[" << s << "] = ";
        b[s].Print();
    }
    cout << "\n";
    
}


inline Int Int::operator+ (const Int& addend) {
    
    Int result(two_pow(b.size())), carry(two_pow(b.size())-1);
    unsigned int p, s;
    
    
    for(p=0; p<addend.b.size(); p++){
        
        for(s=p+1,
            carry.b[p].n = ((b[p].n) & (addend.b[p].n)),
            result.b[p].n = (b[p].n)^(addend.b[p].n);
            s<b.size();
            s++){
            
            carry.b[s].n = ((b[s].n) & (carry.b[s-1].n));
            result.b[s].n = (b[s].n) ^ (carry.b[s-1].n);
            
        }
        
        //the last bit of result is nonzero only if the last carry in the operation is nonzero
        result.b.back() = carry.b.back();
        
    }
    
    return result;

}
