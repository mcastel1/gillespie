#include "fraction.hpp"



inline Fraction::Fraction(void) : BitSet(){}


//construct a Fraction with size bits
inline Fraction::Fraction(unsigned int size) : BitSet(){

    b.resize(size);
    
}
