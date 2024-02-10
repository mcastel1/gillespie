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
    
    //the fraction
    vector<Bits> b;
    //the exponent, encoded in the first 11 bits of e
    vector<Bits> e;
    //the sign
    bool s;
    
public:
    
    Double(void);
    Double(double);
    
   
};
