//
//  bitset.cpp
//  gillespie
//
//  Created by Michele on 12/02/2024.
//

#include "bitset.hpp"


inline BitSet::BitSet(void){
    
    
}

inline BitSet::BitSet(unsigned long long int N){
    
    b.resize(bits(N));
    
}


//set *this to zero
inline void BitSet::Clear(){
    
    for(unsigned int s=0; s<b.size(); s++){
        b[s].n = 0;
    }
    
}

inline void BitSet::Resize(unsigned int size){
    
    b.resize(size);
    
}

inline unsigned int BitSet::GetSize(void){
    
    return ((unsigned int)(b.size()));
    
}



//initialize *this randomly
inline  void BitSet::SetRandom(unsigned int seed){
    
    unsigned int s, p;
    gsl_rng* ran;
    
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    gsl_rng_set(ran, seed);


    for(s=0; s<b.size(); s++){
        for(p=0; p<n_bits; p++){
            b[s].Set(p, (bool)(gsl_rng_uniform_int(ran, 2)));
        }
    }
    
    gsl_rng_free(ran);

    
}

// set all n_bits entries of *this to the respective bits of i. This method requires b to be properly sized
inline void BitSet::SetAll(unsigned long long int i){
    
    Bits m(i);
        
    for(unsigned int s=0; s<bits(m.n); s++){
        (b[s]).SetAll(m.Get(s));
    }
    
    
}


//reize *this in order to contain all bits of i, and set all n_bits entries of *this to the respective bits of i
inline void BitSet::ResizeAndSetAll(unsigned long long int i){
    
    Bits m(i);
    
    Resize(bits(m.n));
    
    for(unsigned int s=0; s<b.size(); s++){
        (b[s]).SetAll(m.Get(s));
    }
    
    
}



void BitSet::Print(void){
    
    unsigned int s;
    
    cout << "\n";
    for(s=0; s<b.size(); s++){
        cout << "[" << s << "] = ";
        b[s].Print();
    }
    cout << "\n";
    
}

//return the unsigned long long int written in the p-th bit of *this
inline unsigned long long int BitSet::Get(unsigned int p){
    
    unsigned int s;
    unsigned long long int result;
    
    for(result=0, s=0; s<GetSize(); s++){
        result += two_pow(s) * (b[s].Get(p));
    }
    
    return result;
    
}


//overload of [] operator. IT IS IMPORTANT THAT THIS RETURNS A REFERENCE, NOT AN UnsignedInt: OTHERWISE THE RETURNED OBJECT, WHEN MODIFIED, WILL NOT CHANGE *this
inline Bits& BitSet::operator [] (const unsigned int& i){
    
    return((b[i]));
    
}


//shift bit-by-bit *this by a number of positions encoded in e
inline void BitSet::operator >>=(const UnsignedInt& e){
    
    
}
