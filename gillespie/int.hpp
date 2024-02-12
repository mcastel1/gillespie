//
//  int.hpp
//  gillespie
//
//  Created by Michele on 07/02/2024.
//

#ifndef int_hpp
#define int_hpp

#include <stdio.h>

#endif /* int_hpp */




//an int represented in base 2 in b
class Int : public BitSet{
    
private:
    
    //here b[i] is the i-th bit of the representation of *this in base 2
    
public:
    
    Int(void);
    Int(unsigned long long int);
    
    void ComplementTo(unsigned int);
    void PrintBase10(void);
    void RemoveFirstSignificantBit(void);

    //bitwise sum
    Int operator + (Int&);
    void operator += (Int&), operator -= (Int&);
    Bits& operator [] (const unsigned int&);
    Bits operator < (const Int&);

    friend class Double;
    
};
