//
//  bits.h
//  gillespie
//
//  Created by Michele on 07/02/2024.
//

#ifndef bits_h
#define bits_h


#endif /* bits_h */


// a collection of bits
class Bits{
  
private:
    unsigned long long int n;
    
public:
    
    Bits();
    Bits(unsigned long long int);
    
    void SetBit(unsigned int, bool);
    bool GetBit(unsigned int);
    void SetRandom(unsigned int);
    void Clear(void);
    void Print(void);
        
    friend class Int;
    
};

