//
//  int.cpp
//  gillespie
//
//  Created by Michele on 07/02/2024.
//

#include "int.hpp"




inline Int::Int(void) : BitSet(){
        
}


inline Int::Int(unsigned long long int N) : BitSet(N){
    
    
}



inline void Int::Resize(unsigned int size){
    
    b.resize(size);
    
}

inline unsigned int Int::GetSize(void){
    
    return ((unsigned int)(b.size()));
    
}

//write the one-complement of *this with respect to a size 'size' of the binary representation and write it into *this
inline void Int::ComplementTo(unsigned int size){
    
    unsigned int s;
    Bits one;
    
    one.SetAll(true);
    this->Resize(size);
    
    //set the first bits common to *this
    for(s=0; s<GetSize(); s++){
        b[s] = (b[s]).Complement();
    }
    for(s=GetSize(); s<this->GetSize(); s++){
        b[s] = one;
    }
    
}





//initialize *this randomly
inline  void Int::SetRandom(unsigned int seed){
    
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
inline void Int::SetAll(unsigned long long int i){
    
    Bits m(i);
        
    for(unsigned int s=0; s<bits(m.n); s++){
        (b[s]).SetAll(m.Get(s));
    }
    
    
}


//reize *this in order to contain all bits of i, and set all n_bits entries of *this to the respective bits of i
inline void Int::ResizeAndSetAll(unsigned long long int i){
    
    Bits m(i);
    
    Resize(bits(m.n));
    
    for(unsigned int s=0; s<b.size(); s++){
        (b[s]).SetAll(m.Get(s));
    }
    
    
}


//set to zero the first bits of *this that is equal to one (stating from the last bit) and leave the others unchanged, write the result in *this
inline void Int::RemoveFirstSignificantBit(void){
    
    int s;
    Bits mask_before, mask_now;
    
//    cout << " before the first significant bit is set to 0:";
//    Print();

    //remove the last significant bit in minuend
    for(s=(this->GetSize())-1, mask_before.SetAll(0); s>=0; s--){
        
        (mask_now.n) = (mask_before.n) | (((*this)[s]).n);
        
        (b[s]).n =  (((*this)[s]).n) & (mask_before.n) & (mask_now.n);
        
        mask_before = mask_now;
        
    }
    
//    cout << " after the first significant bit is set to 0:";
//    Print();
    
    
    
}


void Int::Print(void){
    
    unsigned int s;
    
    cout << "\n";
    for(s=0; s<b.size(); s++){
        cout << "[" << s << "] = ";
        b[s].Print();
    }
    cout << "\n";
    
}


void Int::PrintBase10(void){
    
    unsigned int  p;
    
    cout << "Int in base 10: {";
    for(p=0; p<n_bits; p++){
        
        cout << Get(n_bits-1-p) << " ";
        
    }
    
    cout << "}\n";
        
}


//return the unsigned long long int written in the p-th bit of *this
inline unsigned long long int Int::Get(unsigned int p){
    
    unsigned int s;
    unsigned long long int result;
    
    for(result=0, s=0; s<GetSize(); s++){
        result += two_pow(s) * (b[s].Get(p));
    }
    
    return result;
    
}


//returns *this + m
inline Int Int::operator + (Int& addend) {
    
    Int a;
    
    a=(*this);
    a+=addend;

    return a;

}


//add addend to *this and store the result in *this. This method requires this->GetSize() to be >= addend.GetSize() and this->GetSize() to have been reallocated with the one extra bit before the method is called 
inline void Int::operator += (Int& addend){
    
    Bits carry, t;
    unsigned int p;

    
    for(p=0, carry.Clear();
        p<addend.GetSize();
        p++){
        //run over  bits of addend
        
        (t.n) = (((b[p]).n) ^ (((addend.b)[p]).n) ^ (carry.n));
        (carry.n) = ((((addend.b)[p]).n) & (((b[p]).n) | (carry.n))) | (((b[p]).n) & (carry.n));
        ((b)[p]).n = (t.n);
        
    }
    for(p=addend.GetSize(); p<GetSize()-1; p++){
        //run over the extra bits of augend
        
        (t.n) = (((b[p]).n) ^ (carry.n));
        (carry.n) = (((b[p]).n) & (carry.n));
        (b[p].n) = (t.n);
        
    }
    
//    add the last extra bit
    ((b[p]).n) = (carry.n);
    
    
    
}

//substract m to *this and write the result in *this. THIS FUNCTION REQUIRES THAT *THIS HAS BEEN ALREADY RESIZED WITH AN EXTRA ADDITIONAL ENTRY.
inline void Int::operator -= (Int& m) {
    
    
    Int subtrahend, one;
    
    subtrahend = m;
    
//    cout << "one : ";
//    one.Print();
    one.ResizeAndSetAll(1);
//    cout << "one : ";
//    one.Print();

//    cout << "this:";
//    this->Print();
//    
//    cout << "subtrahend:";
//    subtrahend.Print();
    
    //GIVEN THAT *THIS HAS BEEN RESIZED WITH ONE ADDITIONAL ENTRY AND THAT I WANT TO COMPUTE THE COMPLEMENT WITH RESPECT TO THE ACTUAL SIZE OF THIS (WITHOUT THE ADDITIONAL ENTRY) HERE I CALL  ComplementTo with argument (this->GetSize())-1 RATHER THAN WITH ARGUMENT (this->GetSize())
    subtrahend.ComplementTo((this->GetSize())-1);
    
//    cout << "subtrahend complement:";
//    subtrahend.Print();

    
    (*this) += subtrahend;
    
//    cout << "*this + subtrahend complement:";
//    this->Print();

 
    //THE += operator NEEDS *THIS TO BE RESIZED WITH ONE ADDITIONAL ENTRY EVERY TIME IT IS CALLED -> I RESIZE *this WITH ONE ADDITIONAL ENTRY 
    this->Resize(this->GetSize()+1);
    (*this) += one;
    
//    cout << "*this + subtrahend complement + 1:";
//    this->Print();

    
//    minuend = (minuend + subtrahend.Complement(minuend.GetSize()) + one);
    
//    cout << "minuend + subtrahend.Complement + 1 ";
//    minuend.Print();
 
    
    this->RemoveFirstSignificantBit();

//    cout << "[*this + subtrahend complement + 1 ]_ removed first significant bit:";
//    this->Print();

    
//    cout << "(minuend + ~subtrahend + 1 ).remove first digit";
//    minuend.Print();
 
    
}


//overload of [] operator. IT IS IMPORTANT THAT THIS RETURNS A REFERENCE, NOT AN Int: OTHERWISE THE RETURNED OBJECT, WHEN MODIFIED, WILL NOT CHANGE *this
inline Bits& Int::operator [] (const unsigned int& i){
    
    return((b[i]));
    
}



//Confronto *this con m e scrivo in changer il risultato. changer è uguale a 1 se *this < m e a 0 altrimenti
inline Bits Int::operator < (const Int& m){
    
    int s;
    Bits changer, check;
    
    
    changer = (~(b[GetSize() - 1])) & ((m.b)[GetSize() - 1]);
    check = ((b[GetSize() - 1]) ^ ((m.b)[GetSize() - 1]));
    
    for(s=GetSize()-2; s >=0; s--){
        changer = ((check & changer) | ((~check) & ((~(b[s])) & ((m.b)[s]))) );
        check = (check | ((b[s]) ^ ((m.b)[s])));
    }
    
    return changer;
    
}
