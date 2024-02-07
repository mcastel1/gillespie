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
    
    Int result(b.size()), carry(b.size());
    unsigned int p, s;
    
    
    p=0;
    
    for(s=1,
        carry.b[s] = ((b[s]) & (addend.b[p])),
        (b[s])^= (addend.b[p]);
        s<b.size();
        s++){
        
        carry.b[s] = ((b[s]) & (carry.b[s-1]));
        (b[s])^= (carry.b[s-1]);
        
    }
    
    return result;

}
