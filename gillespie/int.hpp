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
class Int{
    
private:
    
    //b[i] is the i-th bit of the representation of *this in base 2
    vector<Bits> b;
    
public:
    
    Int(void);
    Int(unsigned long long int);
    
    void Resize(unsigned int);
    unsigned int GetSize(void);
    void Clear(void);
    Int Complement(void);
    void SetRandom(unsigned int);
    void SetAll(unsigned long long int);
    void RemoveFirstSignificantBit(void);
    void Print(void);
    void PrintBase10(void);
    
    
//    void SetRandom(unsigned long long int);
    //bitwise sum
    Int operator + (const Int&), operator - (const Int&);
    Bits operator [] (const unsigned int&);

};
