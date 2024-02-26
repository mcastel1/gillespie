#include "fraction.hpp"



inline Fraction::Fraction(void) : BitSet(){}


//construct a Fraction with size bits
inline Fraction::Fraction(unsigned int size) : BitSet(){

    b.resize(size);
    
}


//compute the floor of *this x *multiplicant and store the result in *result. This requires result->GetSize() = GetSize() + (result->GetSize())
inline void Fraction::FloorMultiply(UnsignedInt* multiplicand, UnsignedInt* result){
    
    this->Multiply(multiplicand, result);
    
    
    
}
