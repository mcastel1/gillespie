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

//return the one-complement of *this
Int Int::Complement(void){
    
    Int result(two_pow(b.size())-1);
    
    for(unsigned int s=0; s<b.size(); s++){
        (result.b)[s] = (b[s]).Complement();
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
    
    unsigned int s, p;
    vector<unsigned long long int> result(n_bits);
    
    cout << "Int in base 10: {";
    for(p=0; p<n_bits; p++){
        
        for(result[n_bits-1-p]=0, s=0; s<b.size(); s++){
            result[n_bits-1-p] += two_pow(s) * (b[s].GetBit(n_bits-1-p));
        }
        
        cout << result[n_bits-1-p] << " ";
        
    }
    
    cout << "}\n";
    
    result.clear();
    
}

//returns *this + m
inline Int Int::operator+ (const Int& m) {
    
    
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


inline Int Int::operator- (const Int& subtrahend) {
    
    if(subtrahend.b.size() == (b.size())){
        
        Int result(two_pow(b.size())-1), one(two_pow(b.size())-1), subtrahend_complement;
            
        
        one.SetAll(1);
        
        subtrahend_complement = subtrahend;
        subtrahend_complement = subtrahend_complement.Complement();
        
        result = (*this)+subtrahend_complement+one;
   
        return result;
        
    }else{
        
        cout << "Cannot substract two Ints with different sizes!!\n";
        
        Int dummy;
        return dummy;
        
    }

}

