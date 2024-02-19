//
//  bits.h
//  gillespie
//
//  Created by Michele on 07/02/2024.
//


// a collection of n_bits bits
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
    void SetRandom(gsl_rng*);
    Bits Complement(void);
    void Replace(Bits*, Bits*);
    void Clear(void);
    void Print(void);
        
    friend class UnsignedInt;
    
    Bits operator & (const Bits&), operator | (const Bits&), operator ^ (const Bits&), operator ~(void);
    Bits operator == (Bits&);
    void operator = (const Bits&);
    
};

