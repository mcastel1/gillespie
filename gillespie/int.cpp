//
//  int.cpp
//  gillespie
//
//  Created by Michele on 07/02/2024.
//

#include "int.hpp"




Int::Int(void){
        
}

Int::Int(unsigned long long int N){
    
    b.resize(bits(N));
    
}


//set *this to zero
void Int::Clear(){
    
    unsigned int s;
    
    for(s=0; s<b.size(); s++){
        b[s].n = 0;
    }
    
}


void Int::Resize(unsigned int size){
    
    b.resize(size);
    
}

unsigned int Int::GetSize(void){
    
    return ((unsigned int)(b.size()));
    
}

//return the one-complement of *this with respect to a size 'size' of the binary representation
Int Int::Complement(unsigned int size){
    
    unsigned int s;
    Int result;
    Bits one;
    
    one.SetAll(true);
    result.Resize(size);
    
    //set the first bits common to *this
    for(s=0; s<GetSize(); s++){
        (result.b)[s] = (b[s]).Complement();
    }
    for(s=GetSize(); s<result.GetSize(); s++){
        (result.b)[s] = one;
        
    }
    
    return result;
    
}

//initialize *this randomly
void Int::SetRandom(unsigned int seed){
    
    unsigned int s, p;
    gsl_rng* ran;
    
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    gsl_rng_set(ran, seed);


    for(s=0; s<b.size(); s++){
        for(p=0; p<n_bits; p++){
            b[s].SetBit(p, (bool)(gsl_rng_uniform_int(ran, 2)));
        }
    }
    
    gsl_rng_free(ran);

    
}


//set all n_bits entries of *this to the respective binary values of i
void Int::SetAll(unsigned long long int i){
    
    Bits m(i);
    
    if(b.size() <= n_bits){
        
        for(unsigned int s=0; s<b.size(); s++){
            (b[s]).SetAll(m.GetBit(s));
        }
        
    }else{
        
        cout << "Cannot SetAll if b.size() > n_bits!!\n";
        
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
    
    cout << "Int:\n";
    for(s=0; s<b.size(); s++){
        cout << "b[" << s << "] = ";
        b[s].Print();
    }
    cout << "\n";
    
}

void Int::PrintBase10(void){
    
    unsigned int  p;
    
    cout << "Int in base 10: {";
    for(p=0; p<n_bits; p++){
        
        cout << Get(p) << " ";
        
    }
    
    cout << "}\n";
        
}


//return the unsigned long long int written in the p-th bit of *this
inline unsigned long long int Int::Get(unsigned int p){
    
    unsigned int s;
    unsigned long long int result;
    
    for(result=0, s=0; s<GetSize(); s++){
        result += two_pow(s) * (b[s].GetBit(n_bits-1-p));
    }
    
    return result;
    
}


//returns *this + m
inline Int Int::operator + (const Int& m) {
    
    
    Int augend, carry, addend;
    unsigned int p, s;
    
    //the augend is the largest among *this and m, and the addend the other one
    if(b.size() > m.b.size()){
        augend = (*this);
        addend = m;
    }else{
        augend = m;
        addend = (*this);
    }

    //the carry may propagate until the end of augend -> resize carry correctly
    carry.Resize(augend.GetSize());
    //add an extra bit to augend because the sum may increase its size
    augend.Resize(augend.GetSize()+1);
    
    //    cout << "I am about to make a sum A+B:\n";
    //    cout << "\n\nA:\n";
    //    this->Print();
    //    this->PrintBase10();
    
    //    cout << "\n\nB:\n";
//    addend_copy = m;
    //    addend_copy.Print();
    //    addend_copy.PrintBase10();
    
//    for(augend.Clear(), s=0; s<b.size(); s++){
//        (augend.b)[s] = b[s];
//    }
//    augend.b.back().Clear();
    
    for(p=0; p<addend.GetSize(); p++){
        //sum addend[p] to augend
        
        carry.Clear();
        
        //        cout << "Summing ...";
        //        ((addend_copy.b)[p]).Print();
        
        //run over all bits of augend
        for(s=p+1,
            (((carry.b)[p]).n) = ((((augend.b)[p]).n) & (((addend.b)[p]).n)),
            (((augend.b)[p]).n) ^= (((addend.b)[p]).n);
            s<augend.GetSize()-1;
            s++){
            
            
            (((carry.b)[s]).n) = ((((augend.b)[s]).n) & (((carry.b)[s-1]).n));
            (((augend.b)[s]).n) ^= (((carry.b)[s-1]).n);
            
        }
        
      
        //add the last extra bit, which was not present in *this nor in b
        ((((augend.b)[s]).n) ^= (((carry.b)[s-1]).n));
        
        //        cout << "... Result =";
        //        result.Print();
        
    }
    
    //the last bit of result is nonzero only if the last carry in the operation is nonzero
    return augend;

}


inline Int Int::operator - (const Int& m) {
    
    
    Int minuend, subtrahend, one(1);
    
    
    minuend = (*this);
    subtrahend = m;
    one.SetAll(1);
    
//    cout << "minuend : ";
//    minuend.Print();
//    
//    cout << "subtrahend : ";
//    subtrahend.Print();
    
//    cout << "one : ";
//    one.Print();
    
//    cout << "subtrahend.Complement : ";
//    subtrahend.Complement(minuend.GetSize()).Print();
//    
    minuend = (minuend + subtrahend.Complement(minuend.GetSize()) + one);
    
//    cout << "minuend + subtrahend.Complement + 1 ";
//    minuend.Print();
 
    
    minuend.RemoveFirstSignificantBit();

//    cout << "(minuend + ~subtrahend + 1 ).remove first digit";
//    minuend.Print();
 
    
    return minuend;
    
    
    
}


//overload of [] operator
Bits Int::operator [] (const unsigned int& i){
    
    return(b[i]);
    
}



//Confronto *this con m e scrivo in changer il risultato. changer è uguale a 1 se *this < m e a 0 altrimenti
Bits Int::operator < (const Int& m){
    
    int s;
    Bits changer, check;
    
    
    changer = (~((b[GetSize() - 1]).n)) & (((m.b)[GetSize() - 1]).n);
    check = (((b[GetSize() - 1]).n) ^ (((m.b)[GetSize() - 1]).n));
    
    for(s=GetSize() - 2; s >=0; s--){
        changer = (((check.n) & (changer.n)) | ((~(check.n)) & ((~((b[s]).n)) & (((m.b)[s]).n))) );
        (check.n) = ((check.n) | (((b[s]).n) ^ (((m.b)[s]).n)));
    }
    
    return changer;
    
}
