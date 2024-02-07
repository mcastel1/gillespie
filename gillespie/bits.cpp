//
//  bits.cpp
//  gillespie
//
//  Created by Michele on 07/02/2024.
//

#include <stdio.h>
#include "bits.h"

Bits::Bits(){}

Bits::Bits(unsigned long long int n_in){
    
    n  = n_in;
    
}


//set the i-th entry of input equal to bit
void Bits::SetBit(unsigned int s, bool bit){
    
    unsigned int p;
    unsigned long long int result;
    
    result = 0;
    for(p=0; p<n_bits; p++){
        
        if(p!=s){
            
            result |= (((n >> p) & ullong_1) << p);
            
        }else{
            
            if(bit){
                result |= (ullong_1 << s);
            }
            
        }
        
    }
    
    n = result;
    
}

//return the s-th bit ofinput
bool Bits::GetBit(unsigned int s){
    
    return ((n >> s) & ullong_1);
    
}


void Bits::Print(void){
    
    cout << "Bits = {";
    for(unsigned int s=0; s<n_bits; s++){
        cout << this->GetBit(n_bits-1-s);
    }
    cout << " }";
    
}
