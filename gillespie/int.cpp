//
//  int.cpp
//  gillespie
//
//  Created by Michele on 18/02/2024.
//

#include "int.hpp"


//default constructor
inline Int::Int(void){
        
}

//constructor that resizes m in order to host N
inline Int::Int(unsigned long long int N){
    
    m.resize(bits(N));
    
}


