//
//  double.cpp
//  gillespie
//
//  Created by Michele on 10/02/2024.
//

#include "double.hpp"

//default constructor
inline Double::Double(void){
    
    b.resize(54);
    e.resize(11);
    
}

//set the fraction to zero, the exponent to 1023 and the sign to +
inline void Double::Clear(){
    
    unsigned int p;
    
    //set the fraction to zero
    for(p=0; p<b.size(); p++){
        (b[p]).n = 0;
    }
    
    //set the exponent to 1023
    for(p=0; p<e.size()-1; p++){
        (e[p]).SetAll(true);
    }
    e.back().SetAll(false);
    
    //set the sign to +
    s.SetAll(false);
    
}

