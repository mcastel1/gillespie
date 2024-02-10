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
    
    //the fraction: b has size 54
    vector<Bits> b;
    //the exponent: b has size 11
    vector<Bits> e;
    //the sign
    Bits s;
    
public:
    
    Double(void);
    void Clear(void);
    
};
