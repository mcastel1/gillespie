//
//  lib.cpp
//  gillespie
//
//  Created by Michele on 13/02/2024.
//


//this file includes functions that do not belong a classes

inline unsigned long long int two_pow(unsigned long long int i){
    
    return ((unsigned long long int)gsl_pow_int(2.0, ((int)i)));
    
}

//return the number of bits necessary to write n in base 2
unsigned int inline bits(unsigned long long int n){
    
    unsigned int s;
    
    for(s=0; two_pow(s) <= (unsigned long long int)n; s++){}
    
    return s;
    
}


//print bit-by-bit the double x
inline void bitwise_print_double(const double& x){
    
    uint8_t *bytePointer = (uint8_t*)&x;
    size_t index;
    uint8_t byte;
    int bit;
    unsigned int p;
    vector<bool> result(n_bits);
    
    for(index=0, p=0; index < sizeof(double); index++){
        
        byte = bytePointer[index];
        
        for(bit = 0; bit < 8; bit++, p++){
            
            result[p] = ((bool)(byte & 1));
            byte >>= 1;
            
        }
        
    }
    
    
    cout << "double:";
    for(p=0; p<n_bits; p++){
        
        switch (p) {
            case 0:
                cout << "\n\tSign: ";
                break;
                
            case 1:
                cout << "\n\tExponent: ";
                break;
                
            case 12:
                cout << "\n\tMantissa: ";
                break;
                
            default:
                break;
        }
        
        cout << result[n_bits-1-p];
        
    }
    
    cout << "\n";
    
    
}



