//
//  bitset.cpp
//  gillespie
//
//  Created by Michele on 12/02/2024.
//

#include "bitset.hpp"


inline BitSet::BitSet(void){
    
    
}

inline BitSet::BitSet(unsigned long long int N){
    
    b.resize(bits(N));
    
}
