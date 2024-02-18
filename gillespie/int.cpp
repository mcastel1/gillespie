//
//  int.cpp
//  gillespie
//
//  Created by Michele on 18/02/2024.
//

#include "int.hpp"


//default constructor
inline Int::Int(void): BitSet(){}

//constructor that resizes *this in order to host N
inline Int::Int(long long int N): BitSet(fabs(N)){}


