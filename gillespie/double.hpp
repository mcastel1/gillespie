//
//  double.hpp
//  gillespie
//
//  Created by Michele on 10/02/2024.
//

#ifndef double_hpp
#define double_hpp

#include <stdio.h>

#endif /* double_hpp */

//a double represented in base 2
class Double{
    
private:
    
    //the fraction: b has size 52
    vector<Bits> b;
    //the exponent: e.b has size 11
    Int e;
    //the sign
    Bits s;
    
public:
    
    Double(void);
    void Clear(void);
    void SetAllVertically(double);
    void SetRandom(gsl_rng*);
    void SetRandom(unsigned int);
    void Print(void);
    void PrintBase10(void);

};
