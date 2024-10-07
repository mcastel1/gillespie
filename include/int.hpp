//
//  int.hpp
//  gillespie
//
//  Created by Michele on 18/02/2024.
//


#ifndef int_hpp
#define int_hpp

#include <iostream>

using namespace std;


// a (collection of n_bits) signed interger(s) represented in base 2. The magnitude is stored in the BitSet
class Int: public BitSet{
    
private:
    //the sign
    Bits s;
    
public:
    Int(void);
    Int(long long int);
    void SetAll(long long int);
    
};

#endif
