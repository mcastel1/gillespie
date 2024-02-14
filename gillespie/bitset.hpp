//
//  bitset.hpp
//  gillespie
//
//  Created by Michele on 12/02/2024.
//


class BitSet{
    
private:
    //b[i] is the i-th bit of the BitSet
    vector<Bits> b;
    
public:
    
    BitSet();
    BitSet(unsigned long long int);
    
    void Clear(void);
    void Resize(unsigned int);
    unsigned int GetSize(void);
    void SetRandom(unsigned int);
    void SetAll(unsigned long long int);
    void ResizeAndSetAll(unsigned long long int);
    void RemoveFirstSignificantBit(void);
    unsigned long long int Get(unsigned int);
    void Print(void);

    Bits& operator [] (const unsigned int&);
    void operator >>= (const UnsignedInt&);

    friend class UnsignedInt;
    friend class Double;
    
    
};


