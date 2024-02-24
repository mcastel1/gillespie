//
//  bits.cpp
//  gillespie
//
//  Created by Michele on 07/02/2024.
//

//#include "bits.hpp"

Bits::Bits(){}

Bits::Bits(unsigned long long int n_in){
    
    n  = n_in;
    
}


//set the s-th bit of *this equal to bit
void Bits::Set(unsigned int s, bool bit){
    
    unsigned int p;
    unsigned long long int result;
    
    result = 0;
    for(p=0; p<n_bits; p++){
        
        if(p!=s){
            
            result |= (((n >> p) & ullong_1) << p);
            
        }else{
            
            if(bit){
                result |= (ullong_1 << s);
            }
            
        }
        
    }
    
    n = result;
    

}




//set all n_bits entries of *this equal to *bit
inline void Bits::SetAll(bool bit){
    
    for(unsigned int s=0; s<n_bits; s++){
        this->Set(s, bit);
    }
    
}


//return the s-th bit ofinput
inline bool Bits::Get(unsigned int s){
    
    return ((n >> s) & ullong_1);
    
}


//set *this randomly with seed seed
inline void Bits::SetRandom(unsigned int seed){
    
    gsl_rng* ran;
    
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    gsl_rng_set(ran, seed);

    SetRandom(ran);
    
    gsl_rng_free(ran);

}

//set *this randomly with random number generator ran
inline void Bits::SetRandom(gsl_rng* ran){
    
    unsigned int s;
    
    for(s=0; s<n_bits; s++){
        Set(s, (bool)(gsl_rng_uniform_int(ran, 2)));
    }
    
}


//return the one's complement of *this 
inline inline Bits Bits::Complement(void){
    
    return(~(*this));
    
}


//compute the one's complement of *this and write it into *this
inline void Bits::ComplementTo(void){
    
    (*this) = (~(*this));
    
}


//replace bit-by-bit *this with replacer if check = true, and leave *this unchanged if check = false
inline void Bits::Replace(Bits* replacer,  Bits* check){
    
    (*this) =  (((*this) & (~(*check))) | ((*replacer) & (*check)));
    
}


//swap bit-by-bit the pair {*this, *a} if *check = true and write the result in {*this, *a}, and leave *this and *a unchanged if *check = false, where *work is a temporary variable needed to store stuff. This method requires *a and *work to be allocated
inline void Bits::Swap(Bits* a, Bits& check, Bits* work_space){

    //store temporarily *this in *work
    (*work_space) = (*this);
    
    //swap *this with *a according to *check and write the result in *this
    (*this) = ((*this) & (~check)) | ((*a) & check);
    //swap *a with *this according to *check and write the result in *a
    (*a) = ((*a) & (~check)) | ((*work_space) & check);
    
}


//set all bits of *this to 0
inline void Bits::Clear(void){
    
    n = 0;
    
}

inline void Bits::Print(string title){
    
    cout << title << "{ ";
    for(unsigned int s=0; s<n_bits; s++){
        cout << this->Get(n_bits-1-s);
    }
    cout << " }\n";
    
}

inline void Bits::operator = (const Bits& m){
    
    n = (m.n);
    
    
}


//return (this->n) | (m.n) (bitwise OR)
inline Bits Bits::operator | (const Bits& m){
    
    return Bits((n | (m.n)));
    
}


//return (this->n) & (m.n) (bitwise AND)
inline Bits Bits::operator & (const Bits& m){
    
    return Bits((n & (m.n)));
    
}


//return (this->n) ^ (m.n) (bitwise xOR)
inline Bits Bits::operator ^ (const Bits& m){
    
    return Bits((n ^ (m.n)));
    
}



//apply a bit-by-bit negation to *this and return the result
inline Bits Bits::operator ~ (void){
    
    return Bits((~n));

    
}


//this is not a method of the Bits class, but an ordinary function which had to be declared in this file because it need to know who the Bits type is
inline Bits operator ~ (const Bits& m){
    
    return Bits((~(m.n)));
    
}

//return (bit-by-bit) true if *this == m, false otherwise
inline Bits Bits::operator == (Bits& m){
    
    return(Bits(~(n ^ (m.n))));
    
}


inline void Bits::operator &= (const Bits& m){
    
    n &= (m.n);
    
}


inline void Bits::operator &= (Bits* m){
    
    n &= (m->n);
    
}

inline void Bits::operator ^= (Bits* m){
    
    n ^= (m->n);
    
}
