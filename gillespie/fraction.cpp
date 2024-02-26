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

//get  bit-by-bit the value in base 10 of *this and write it in *v
inline void Fraction::GetBase10(vector<double>* v){
    
    unsigned int p, s;
    
    v->resize(n_bits);
    
    for(s=0; s<n_bits; s++){
        
        for(p=0, (*v)[s]=0.0; p<GetSize(); p++){
            (*v)[s] += gsl_pow_int(2.0, p-GetSize()) * b[p].Get(s);
        }
        
    }
    
}

inline void Fraction::PrintBase10(string title){
    
    unsigned int p;
    vector<double> v;
    
    cout << title << ": {";
    for(GetBase10(&v), p=0; p<n_bits; p++){
        
        cout << v[n_bits-1-p] << " ";
        
    }
    
    cout << "}" << endl;
    
    
}
