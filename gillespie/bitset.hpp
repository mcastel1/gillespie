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
    void Normalize(void);
    void Normalize(unsigned int);
    void Resize(unsigned long long int);
    unsigned int GetSize(void);
    void SetRandom(unsigned int);
    void SetAll(unsigned long long int);
    void SetAllFromDouble(double);
    void SetFromDouble(unsigned int, double);
    void ComplementTo(void);
    void ComplementTo(unsigned int);
    void ResizeAndSetAll(unsigned long long int);
    UnsignedInt PositionOfFirstSignificantBit(void);
    void RemoveFirstSignificantBit(void);
    unsigned long long int Get(unsigned int);
    void Print(string);

    //bitwise sum and substraction
    void MinusEqualWithoutResizing(BitSet*), PlusEqualWithoutResizing(BitSet*);
    BitSet operator + (BitSet*), operator - (BitSet*), operator << (Bits*);
    void operator += (BitSet*), operator += (const Bits*), operator -= (BitSet*), operator *= (BitSet*);
    Bits& operator [] (const unsigned int&);
    Bits operator == (BitSet&), operator < (const BitSet&);
    void operator >>= (UnsignedInt*), operator <<= (UnsignedInt*), operator >>= (const Bits*), operator <<= (const Bits*), operator &= (Bits*);

    friend class UnsignedInt;
    friend class Double;
    
    
};



