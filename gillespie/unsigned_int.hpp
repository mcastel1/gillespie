//
//  int.hpp
//  gillespie
//
//  Created by Michele on 07/02/2024.
//

//an int represented in base 2 in b
class UnsignedInt : public BitSet{
    
private:
    
    //here b[i] is the i-th bit of the representation of *this in base 2
    
public:
    
    UnsignedInt(void);
    UnsignedInt(unsigned long long int);
    
    void ComplementTo(unsigned int);
    void PrintBase10(void);
    void RemoveFirstSignificantBit(void);
    void Replace(UnsignedInt*, Bits*);

    //bitwise sum and substraction
    UnsignedInt operator + (UnsignedInt&), operator - (UnsignedInt&);
    void operator += (UnsignedInt&), operator -= (UnsignedInt&);
    Bits operator < (const UnsignedInt&);

    friend class Double;
    
};
