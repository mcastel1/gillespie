//
//  bitset.cpp
//  gillespie
//
//  Created by Michele on 12/02/2024.
//

//#include "bitset.hpp"


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


//swap bit-by-bit the pair {*this, *a} if *check = true and write the result in {*this, *a}, and leave *this and *a unchanged if *check = false, where *work_space is a temporary variable needed to store stuff. This method requires *a and *work_space to be allocated and *this and *a to have the same size
inline void BitSet::Swap(BitSet* a, Bits& check, Bits* work_space){
    
    for(unsigned int s=0; s<GetSize(); s++){
        
        b[s].Swap(&((a->b)[s]), check, work_space);
        
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


inline void BitSet::Print(string title){
    
    unsigned int s;
    
    cout << title << endl;
    for(s=0; s<b.size(); s++){
        cout << "[" << s << "] = ";
        //extra space to align vertically the output
        if(s < 10){cout << " ";}
        b[s].Print("");
    }
    cout << endl;
    
}

//return (bit-by-bit) true if *this == m, and false otherwise. This method requires *this and m to have the same size
inline Bits BitSet::operator == (BitSet& m){
    
    unsigned int p;
    Bits result;
    
    if(GetSize() == m.GetSize()){
        //*this and m have the same size -> check if they are equal
        
        //run through all entries b[p], as soon as there is an entry of *this that is different form the corresponding entry of m, set result to false
        for(p=0, result.SetAll(true); p<GetSize(); p++){
            
            result &= (b[p] == (m.b)[p]);
            
        }
        
    }else{
        //*this and m have different sizes -> set the result equal to false
        
        result.SetAll(false);
        
    }
    
    return result;
    
}

//Confronto *this con m e scrivo in result il risultato. result è uguale a 1 se *this < m e a 0 altrimenti
inline Bits BitSet::operator < (const BitSet& m){
    
    int s;
    Bits result, check;
    
    
    result = (~(b[GetSize() - 1])) & ((m.b)[GetSize() - 1]);
    check = ((b[GetSize() - 1]) ^ ((m.b)[GetSize() - 1]));
    
    for(s=GetSize()-2; s >=0; s--){
        result = ((check & result) | ((~check) & ((~(b[s])) & ((m.b)[s]))) );
        check = (check | ((b[s]) ^ ((m.b)[s])));
    }
    
    return result;
    
}


//shift bit-by-bit to the left the entries of  b[GetSize()-1], b[GetSize()-2] , ... b[0] in *this by *m (thus by either one position or zero positions), replace the remaining entries b[] by all zeros and write the result in *this
inline BitSet BitSet::operator << (Bits* m){
    
    BitSet t = (*this);
    t <<= m;
    return t;
    
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



//return *this + *addend
inline BitSet BitSet::operator + (BitSet* addend) {
    
    BitSet a;
    
    a = (*this);
    a += addend;

    return a;

}


//return *this - m
inline BitSet BitSet::operator - (BitSet* addend) {
    
    BitSet t;
    
    t = (*this);
    t -= addend;

    return t;

}


//return *this + *addend and write the carry in *carry
inline BitSet BitSet::Add(BitSet* addend, Bits* carry) {
    
    BitSet a;
    
    a = (*this);
    a.AddTo(addend, carry);

    return a;

}



//return *this + *subrahend and write the borrow in *borrow
inline BitSet BitSet::Substract(BitSet* subtrahend, Bits* borrow) {
    
    BitSet t;
    
    t = (*this);
    t.SubstractTo(subtrahend, borrow);

    return t;

}


//add addend to *this,  and store the result in *this. This method requires this->GetSize() to be >= addend.GetSize()
inline void BitSet::operator += (BitSet* addend){
    
    Bits carry, t;
    
    AddTo(addend, &carry);
    
    //    add the last extra bit
    //******** THIS MAY BE TIME CONSUMING ********
    b.push_back(carry);
    
}


//same as BitSet::operator +=  but the last bit is not pushed back into b, but written into *carry
inline void BitSet::AddTo(BitSet* addend, Bits* carry){
    
    Bits t;
    unsigned int p;

    
    for(p=0, carry->Clear();
        p<addend->GetSize();
        p++){
        //run over  bits of addend
        
        (t.n) = (((b[p]).n) ^ (((addend->b)[p]).n) ^ (carry->n));
        (carry->n) = ((((addend->b)[p]).n) & (((b[p]).n) | (carry->n))) | (((b[p]).n) & (carry->n));
        (b[p]).n = (t.n);
        
    }
    for(p=addend->GetSize(); p<GetSize(); p++){
        //run over the extra bits of augend
        
        (t.n) = (((b[p]).n) ^ (carry->n));
        (carry->n) = (((b[p]).n) & (carry->n));
        (b[p].n) = (t.n);
        
    }
    
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

//add bit-by-bit addend (which here is either 1 or 0) to *this and store the result in *this and the carry in *carry. This method requires this->GetSize() to be > 1
inline void BitSet::AddTo(Bits* addend, Bits* carry){
        
    Bits t;
    unsigned int p;

    //sum the only bit of addend
    (carry->n) = ((addend->n) & ((b[0]).n));
    (b[0]).n = (((b[0]).n) ^ (addend->n));
    
    for(p=1; p<GetSize(); p++){
        //run over the extra bits of augend
        
        (t.n) = (((b[p]).n) ^ (carry->n));
        (carry->n) = (((b[p]).n) & (carry->n));
        (b[p].n) = (t.n);
        
    }
        
    
}




//substract m to *this and write the result in *this
inline void BitSet::operator -= (BitSet* subtrahend) {
    
    
    BitSet subtrahend_t;
    
    subtrahend_t = (*subtrahend);
    
//    cout << "this:";
//    this->Print();
//
//    cout << "subtrahend:";
//    subtrahend.Print();
    
    //GIVEN THAT *THIS HAS BEEN RESIZED WITH ONE ADDITIONAL ENTRY AND THAT I WANT TO COMPUTE THE COMPLEMENT WITH RESPECT TO THE ACTUAL SIZE OF THIS (WITHOUT THE ADDITIONAL ENTRY) HERE I CALL  ComplementTo with argument (this->GetSize())-1 RATHER THAN WITH ARGUMENT (this->GetSize())
    subtrahend_t.ComplementTo((this->GetSize()));
    
//    cout << "subtrahend complement:";
//    subtrahend.Print();

    
    (*this) += (&subtrahend_t);
    
//    cout << "*this + subtrahend complement:";
//    this->Print();
 
    (*this) += (&BitSet_one);
    
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


//do the same as BitSet::operator -= but without resizing operations. This method requires this->GetSize() to be >= addend.GetSize()
inline void BitSet::SubstractTo(BitSet* subtrahend, Bits* borrow) {
    
    unsigned int p;
    Bits t;
    
    for(p=0, borrow->Clear();
        p<subtrahend->GetSize();
        p++){
        //run over  bits of subtrahend
        
        (t.n) = (((b[p]).n) ^ (((subtrahend->b)[p]).n) ^ (borrow->n));
        //        (borrow && (! minuend || subtrahend)) || (! minuend && subtrahend)
        (borrow->n) = ((borrow->n) & ((~((b[p]).n)) | (((*subtrahend)[p]).n))) | ((~((b[p]).n)) & (((*subtrahend)[p]).n));
        (b[p]).n = (t.n);
        
    }

    for(p=subtrahend->GetSize(); p<GetSize(); p++){
        //run over the extra bits of minuend
        
        (t.n) = (((b[p]).n) ^ (borrow->n));
        (borrow->n) = ((~((b[p]).n)) & (borrow->n));
        (b[p].n) = (t.n);
        
    }
    
}


//write the one-complement of *this with respect to a size 'size' of the binary representation and write it into *this
inline void BitSet::ComplementTo(unsigned int size){
    
    unsigned int s;
    
    
    //set the first bits common to *this
    for(s=0; s<GetSize(); s++){
        b[s] = (b[s]).Complement();
    }
    
    Resize(size);

    //set the remaining bits equal to one 
    for(; s<GetSize(); s++){
        b[s] = Bits_one;
    }
    
}


//write the one-complement of *this  and write it into *this
inline void BitSet::ComplementTo(void){
    
    for(unsigned int s=0; s<GetSize(); s++){
        (b[s]).ComplementTo();
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



//shift bit-by-bit to the right the entries of  b[GetSize()-1], b[GetSize()-2] , ... b[0] in *this by *l (thus by either one position or zero positions) and replace the remaining entries b[] by all zeros
inline void BitSet::operator >>= (Bits* l){
    
    int m;
        
    //run through the components of this->b and shift them
    //in this first loop, I run over the first chunk of entries of b: m = 0, ..., b.size() - 2^n-1 and I replace the m-th component of b with the m+2^n-th compoennt if e[n]=true, and do nothing otherwise
    for(m=0; m<(this->GetSize())-1; m++){
        
        b[m].Replace(
                     //the element # m+1 in b
                     (b.data()) + (m+1),
                     l
                     );
        
    }
    
    //I consider the last entry of b: I can no longer replace it with b[m+1] as in the loop above, becuase b[m+1] does not exist in b -> I replace it with zero
    b.back().Replace(
                     //a Bits filled with zeros
                     &Bits_zero,
                     l
                     );
    
}



//shift bit-by-bit to the left the entries of  b[GetSize()-1], b[GetSize()-2] , ... b[0] in *this by *l (thus by either one position or zero positions), replace the remaining entries b[] by all zeros and write the result on *this
inline void BitSet::operator <<= (Bits* l){
    
    int m;
    
    
    //run through the components of this->b and shift them
    //in this first loop, I run over the first chunk of entries of b:  and I replace  if e=true, and do nothing otherwise
    for(m=(this->GetSize())-1; m>0; m--){
        
        b[m].Replace(
                     //the element # m+1 in b
                     (b.data()) + (m-1),
                     l
                     );
        
    }
    
    //I consider the first entry (b[0]) of b: I can no longer replace it with b[-1] as in the loop above, becuase b[-1] does not exist in b -> I replace it with zero
    b.front().Replace(
                     //a Bits filled with zeros
                     &Bits_zero,
                     l
                     );
    
}


//perform (bit-by-bit) an & between  b[s] and *m ,and write the result in b[s] for all s = 0 ... GetSize()
inline void BitSet::operator &= (Bits* m){
    
//    for(unsigned int s=0; s<GetSize(); s++){
//
//        b[s] &= m;
//
//    }
  
    AndTo(m, 0, GetSize());
    
}


//perform (bit-by-bit) an & between  b[s] and *m ,and write the result in b[s] for all s = start, ..., end-1
inline void BitSet::AndTo(Bits* m, unsigned int start, unsigned int end){
    
    for(unsigned int s=start; s<end; s++){
        
        b[s] &= m;
        
    }
    
}


//multiply *this by addend (as if they were two UnsignedInts)  and store the result in *this. This method requires this->GetSize() to be >= addend.GetSize(). once this method is called, *this has size [size of *this before the method is called] + multiplicand.GetSize()
inline void BitSet::operator *= (BitSet* multiplicand){
    
    unsigned int s;
    BitSet result, t;
    

    //THIS MAY SLOW DOWN THE CODE
    //resize *this and result in order to be large enough to host the result
    Resize(GetSize() + (multiplicand->GetSize()));
    for(s=GetSize()-(multiplicand->GetSize()); s<GetSize(); s++){
        b[s].SetAll(false);
    }
    result.Resize(GetSize());
    //THIS MAY SLOW DOWN THE CODE
    

    for(s=0, result.SetAll(0); s<multiplicand->GetSize(); s++){
        //multiply by the s-th element of multiplicand: at each step of this loop *this is shifted by one unit to the left
        
        //the temporarly variable t is set equal to the original value of *this multiplyed by 2^s
        t = (*this);
        //I perform this & to multiply by the s-th bit of the multiplicand
        t &= &((*multiplicand)[s]);
        
        //add the partial sum to the result
        result += &t;
        
        //shift this
        (*this) <<= &Bits_one;

    }
    
    //during the for loop above, the line result += &t has uselessly increased the size of result -> THIS MAY SLOW DOWN THE CODE -> I resize result to the maximum size it can have after the multiplication 
    result.Resize(GetSize());
    //result now is complete: set *this equal to result
    (*this) = result;
    
}



//multiply *this by *multiplicand and write the result in *result. This method reqires *result to be large enough to host the result:
/*
 
 *this = 2^0 (this->b)[0] + .... + 2^{(this->b).size()-1} (this->b)[(this->b).size()-1]
 *multiplicand = 2^0 (multiplicand->b)[0] + .... + 2^{(multiplicand->b).size()-1} (multiplicand->b)[(multiplicand->b).size()-1]
 
 (*this) x (*multiplicand) = 2^{0}... + .... + 2^{(this->b).size()-1 + (multiplicand->b).size()-1}}
 thus
 result->GetSize() >= (this-GetSize()) + (multiplicand->GetSize() - 1

 the times are from  ./main.o -s 0 -S 6
 */
inline void BitSet::Multiply(BitSet* multiplicand, BitSet* result){
    
    unsigned int s, p;
    Bits carry, t, u;
        
    //set work_space_b equal to *this
    //1.2 e-2 s
//    work_space_b->SetAll(0);
//    //9e-3 s
//    for(s=0; s<GetSize(); s++){
//        (work_space_b->b)[s] = b[s];
//    }
    
    for(s=0, result->SetAll(0); s<multiplicand->GetSize(); s++){
        //multiply by the s-th element of multiplicand: at each step of this loop *this is shifted by one unit to the left
        
        
        //the temporarly variable work_space is set equal to the original value of *this multiplyed by 2^s
        //1.8e-2 s
//        (*work_space_a) = (*work_space_b);
        
        
        //I perform this '&' to multiply by *work_space the s-th bit of the multiplicand
        //1.5 e-2 s
//        (*work_space_a) &= &((*multiplicand)[s]);
//        work_space_a->AndTo(&((*multiplicand)[s]), s, s+(multiplicand->GetSize()));
        
        for(p=0, carry.Clear(); p<GetSize(); p++){
            
            (u.n) = ((((*multiplicand)[s]).n) & ((b[p]).n));
            (t.n) = ((((result->b)[p+s]).n) ^ (u.n) ^ (carry.n));
            
            (carry.n) = ((u.n) & ((((result->b)[p+s]).n) | (carry.n))) | ((((result->b)[p+s]).n) & (carry.n));
            ((result->b)[p+s]).n = (t.n);
            
        }
        ((result->b)[p+s]).n = (carry.n);

        
        //add the partial sum to the result
        //2.4e-2 s
//        result->AddTo(work_space_a, &carry);
        
        //shift *this = *work_space_b
        //2.2 e-2 s
//        (*work_space_b) <<= &Bits_one;

    }
    
}
