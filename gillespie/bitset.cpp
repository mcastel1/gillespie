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

inline void BitSet::Resize(unsigned long long int size){
    
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

//set all n_bits entries of *this to the respective bits of i. This method requires  *this to be properly sized to contain i
inline void BitSet::SetAll(unsigned long long int i){
    
    unsigned int s;
    Bits m(i);
          
    //set the first bits(m.n) bits of *this equal to the bits of i
    for(s=0; s<bits(m.n); s++){
        (b[s]).SetAll(m.Get(s));
    }
    //set the remaining bits of *this, if any, to false (0)
    for(s=bits(m.n); s<GetSize(); s++){
        (b[s]).SetAll(false);
    }
    
}


//set all n_bits entries of *this equal to the entries stored (in IEEE754 format) in the mantissa of x. This requires b to be properly sized
inline void BitSet::SetAllFromDouble(double x){
    
    for(unsigned int s=0; s<n_bits; s++){
        SetFromDouble(s, x);
    }
    
}


//set the s-th bit entry of *this equal to the entries stored (in IEEE754 format) in the mantissa of x. This requires b to be properly sized
inline void BitSet::SetFromDouble(unsigned int s, double x){
    
    uint8_t *bytePointer = (uint8_t*)&x;
    size_t index;
    uint8_t byte;
    int bit;
    unsigned int p;
    
    for(index=0, p=0; index<sizeof(double); index++){
        
        byte = bytePointer[index];
        
        for(bit=0; bit<8; bit++, p++){
            
            if(p < (this->GetSize())){
                b[p].Set(s, ((bool)(byte & 1)));
            }else{
                break;
                break;
            }
            
            byte >>= 1;
            
        }
        
    }
    
}



//reize *this in order to contain all bits of i, and set all n_bits entries of *this to the respective bits of i
inline void BitSet::ResizeAndSetAll(unsigned long long int i){
    
    Resize(bits(i));
    SetAll(i);
    
}


void BitSet::Print(void){
    
    unsigned int s;
    
    cout << endl;
    for(s=0; s<b.size(); s++){
        cout << "[" << s << "] = ";
        //extra space to align vertically the output
        if(s < 10){cout << " ";}
        b[s].Print();
    }
    cout << endl;
    
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



//return *this + m
inline BitSet BitSet::operator + (BitSet* addend) {
    
    BitSet a;
    
    a = (*this);
    a += addend;

    return a;

}



//return *this - m
inline BitSet BitSet::operator - (BitSet* addend) {
    
    BitSet a;
    
    a = (*this);
    a -= addend;

    return a;

}


//add addend to *this,  and store the result in *this. This method requires this->GetSize() to be >= addend.GetSize()
inline void BitSet::operator += (BitSet* addend){
    
    Bits carry, t;
    unsigned int p;

    
    for(p=0, carry.Clear();
        p<addend->GetSize();
        p++){
        //run over  bits of addend
        
        (t.n) = (((b[p]).n) ^ (((addend->b)[p]).n) ^ (carry.n));
        (carry.n) = ((((addend->b)[p]).n) & (((b[p]).n) | (carry.n))) | (((b[p]).n) & (carry.n));
        ((b)[p]).n = (t.n);
        
    }
    for(p=addend->GetSize(); p<GetSize(); p++){
        //run over the extra bits of augend
        
        (t.n) = (((b[p]).n) ^ (carry.n));
        (carry.n) = (((b[p]).n) & (carry.n));
        (b[p].n) = (t.n);
        
    }
    
    //    add the last extra bit
    //******** THIS MAY BE TIME CONSUMING ********
    b.push_back(carry);
    
//    Normalize();
    
}

//remove useless bits on the tail of *this that contain all 0s
inline void BitSet::Normalize(void){
    
    int p;
    
    for(p=GetSize()-1; p>=0; p--){
        
        if((b[p]).n == 0){
            b.pop_back();
        }else{
            break;
        }
        
    }
    
}

//remove useless bits on the tail of *this that contain all 0s, as long as this deletion does not make the size of *this < than n
inline void BitSet::Normalize(unsigned int n){
    
    int p;
    
    for(p=GetSize()-1; p>=0; p--){
        
        if(((b[p]).n == 0) && (GetSize() >= n)){
            b.pop_back();
        }else{
            break;
        }
        
    }
    
}

//add bit-by-bit addend (which here is either 1 or 0) to *this and store the result in *this. This method requires this->GetSize() to be > 1 and assumes that *this and addend are such that there is no overflow while doing this operation
inline void BitSet::operator += (const Bits* addend){
        
    Bits carry, t;
    unsigned int p;

    //sum the only bit of addend
    (carry.n) = ((addend->n) & ((b[0]).n));
    (b[0]).n = (((b[0]).n) ^ (addend->n));
    
    for(p=1; p<GetSize()-1; p++){
        //run over the extra bits of augend
        
        (t.n) = (((b[p]).n) ^ (carry.n));
        (carry.n) = (((b[p]).n) & (carry.n));
        (b[p].n) = (t.n);
        
    }
    
    //    add the last extra bit to b. This assumes that there cannot be overflow in this operation
    (b.back().n) ^= (carry.n);
    
//    Normalize();
    
}

//substract m to *this and write the result in *this
inline void BitSet::operator -= (BitSet* m) {
    
    
    BitSet subtrahend, one;
    
    subtrahend = (*m);
    
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
    subtrahend.ComplementTo((this->GetSize()));
    
//    cout << "subtrahend complement:";
//    subtrahend.Print();

    
    (*this) += (&subtrahend);
    
//    cout << "*this + subtrahend complement:";
//    this->Print();
 
    (*this) += (&one);
    
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


//write the one-complement of *this with respect to a size 'size' of the binary representation and write it into *this
inline void BitSet::ComplementTo(unsigned int size){
    
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



//set to zero the first bits of *this that is equal to one (starting from the last bit) and leave the others unchanged, write the result in *this
inline void BitSet::RemoveFirstSignificantBit(void){
    
    int s;
    Bits check_old, check_new;
    
//    cout << " before the first significant bit is set to 0:";
//    Print();

    //remove the last significant bit in minuend
    for(s=(this->GetSize())-1, check_old.SetAll(0); s>=0; s--){
        
        (check_new.n) = (check_old.n) | (((*this)[s]).n);
        
        (b[s]).n =  (((*this)[s]).n) & (check_old.n) & (check_new.n);
        
        check_old = check_new;
        
    }
    
//    cout << " after the first significant bit is set to 0:";
//    Print();
    

}



//shift bit-by-bit to the right the entries of  b[0] b[1] ... in *this by *e (thus by either one position or one position) and replace the remaining entries b[] by all zeros
inline void BitSet::operator >>=(const Bits* e){
    
    int m;
    Bits zero, e_saved;
    
    zero.SetAll(false);
    e_saved = (*e);
    
    //run through the components of this->b and shift them
    //in this first loop, I run over the first chunk of entries of b: m = 0, ..., b.size() - 2^n-1 and I replace the m-th component of b with the m+2^n-th compoennt if e[n]=true, and do nothing otherwise
    for(m=0; m<(this->GetSize())-1; m++){
        
        b[m].Replace(
                     //the element # m+1 in b
                     (b.data()) + (m+1),
                     &e_saved
                     );
        
    }
    
    //I consider the last entry of b: I can no longer replace it with b[m+1] as in the loop above, becuase b[m+1] does not exist in b -> I replace it with zero
    b.back().Replace(
                     //a Bits filled with zeros
                     &zero,
                     &e_saved
                     );
    
}



//shift bit-by-bit to the left the entries of  b[0] b[1] ... in *this by *e (thus by either one position or one position) and replace the remaining entries b[] by all zeros
inline void BitSet::operator <<=(const Bits* e){
    
    int m;
    Bits zero, e_saved;
    
    zero.SetAll(false);
    e_saved = (*e);
    
    //run through the components of this->b and shift them
    //in this first loop, I run over the first chunk of entries of b:  and I replace  if e=true, and do nothing otherwise
    for(m=(this->GetSize())-1; m>0; m--){
        
        b[m].Replace(
                     //the element # m+1 in b
                     (b.data()) + (m-1),
                     &e_saved
                     );
        
    }
    
    //I consider the first entry (b[0]) of b: I can no longer replace it with b[-1] as in the loop above, becuase b[-1] does not exist in b -> I replace it with zero
    b.front().Replace(
                     //a Bits filled with zeros
                     &zero,
                     &e_saved
                     );
    
}



