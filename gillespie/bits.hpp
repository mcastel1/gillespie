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

public:
    
    unsigned long long int n;
    
    Bits();
    Bits(unsigned long long int);
    
    void Set(unsigned int, bool);
    void SetAll(bool);
    bool Get(unsigned int);
    void SetRandom(unsigned int);
    Bits Complement(void);
    void Clear(void);
    void Print(void);
        
    friend class Int;
    
    Bits operator & (const Bits&), operator | (const Bits&), operator ^ (const Bits&);
    
};

