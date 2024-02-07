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


inline Int Int::operator+ (const Int& addend) {
    
    Int result(b.size()+1), carry(b.size());
    unsigned int p, s;
    
    
    for(p=0; p<addend.b.size(); p++){
        
        for(s=p+1,
            carry.b[p].n = ((b[p].n) & (addend.b[p].n)),
            (b[p].n) ^= (addend.b[p].n);
            s<b.size();
            s++){
            
            carry.b[s].n = ((b[s].n) & (carry.b[s-1].n));
            (b[s].n) ^= (carry.b[s-1].n);
            
        }
        
    }
    
    return result;

}
