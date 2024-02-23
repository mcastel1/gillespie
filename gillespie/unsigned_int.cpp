//
//  int.cpp
//  gillespie
//
//  Created by Michele on 07/02/2024.
//

#include "unsigned_int.hpp"



//default constructor
inline UnsignedInt::UnsignedInt(void) : BitSet(){}

//constructor taht resizes *this in ordert to host N
inline UnsignedInt::UnsignedInt(unsigned long long int N) : BitSet(N){}


//if this->GetSize() == replacer->GetSize(), replace bit-by-bit all bs of *this with the respective bs of *replacer, and leave *this unchanged otherwise
inline void UnsignedInt::Replace(UnsignedInt* replacer, Bits* check){
    
    if((this->GetSize()) == (replacer->GetSize())){
        
        for(unsigned int s=0; s<(this->GetSize()); s++){
            b[s].Replace((replacer->b.data()) + s, check);
        }
        
    }
    
}


//set the s-th bit of *this equal to i. This requires b to be sized properly
inline void UnsignedInt::Set(unsigned int s, unsigned long long int i){
    
    unsigned int p;
    Bits n(i);
    
    for(p=0; p<b.size(); p++){
        b[p].Set(s, ((bool)(n.Get(p))));
    }
    
}



void UnsignedInt::PrintBase10(string title){
    
    unsigned int  p;
    vector<unsigned long long int> v;
    
    cout << title << ": {";
    for(p=0, GetBase10(v); p<n_bits; p++){
        
        cout << v[n_bits-1-p] << " ";
        
    }
    
    cout << "}" << endl;
        
}


void UnsignedInt::GetBase10(vector<unsigned long long int>& v){
    
    unsigned int p;
    for(p=0, v.resize(n_bits); p<n_bits; p++){
        
         v[p] = Get(p);
        
    }
    
}


void UnsignedInt::operator = (BitSet m){
    
    b = m.b;
    
}


//I am obliged to put this method definition here, because this method needs the full declaration of the UnsignedInt class before it is declared
//shift bit-by-bit the entries of  b[51] b[50] ... in *this by a number of positions to the right (>>) encoded in *e and replace the remaining entries b[] by all zeros
inline void BitSet::operator >>=(UnsignedInt* e){
    
    unsigned int n;
    int m;
    Bits zero;
    
    zero.SetAll(false);
    
    
    for(n=0; n<(e->GetSize()); n++){
        //shift by 2^n positions according to e[n]
        
        //run through the components of this->b and shift them
        
        //in this first loop, I run over the first chunk of entries of b: m = 0, ..., b.size() - 2^n-1 and I replace the m-th component of b with the m+2^n-th compoennt if e[n]=true, and do nothing otherwise
        for(m=0; m<GetSize()-gsl_pow_int(2, n); m++){

            b[m].Replace(
                         //the element # m+2^n in b
                         &(b[m+gsl_pow_int(2, n)]),
                         //the element #n in e
                         &((e->b)[n])
                         );
        
            
        }
        
        //in this loop, I run over the second chunk of entries of b: m =b.size() - 2^n , ..., b.size(). I can no longer replace b[m] with b[m+2^n] as in the loop above, becuase b[m+2^n] does not exist in b -> I replace it with zero. Note that if 2^n > b.size(), this second loop must cover the entire vector b -> I set as starting value of m  max(((int)GetSize())-((int)gsl_pow_int(2, n)), 0)
        for(m = max(((int)GetSize())-((int)gsl_pow_int(2, n)), 0); (m<GetSize()); m++){
                     
            b[m].Replace(
                         //a Bits filled with zeros
                         &zero,
                         //the element #n in e
                         &((e->b)[n])
                         );
        
            
        }
        
    }
    
    
}


//shift bit-by-bit the entries of  b[51] b[50] ... in *this by a number of positions to the left (<<) encoded in *e and replace the remaining entries b[] by all zeros
inline void BitSet::operator <<=(UnsignedInt* e){
    
    unsigned int n;
    int m;
    Bits zero;
    
    zero.SetAll(false);
    
    
    for(n=0; n<(e->GetSize()); n++){
        //shift by 2^n positions according to e[n]
        
        //run through the components of this->b and shift them
        
        //in this first loop, I run over the first chunk of entries of b: m = b.size()-1, ..., 2^n and I replace the m-th component of b with the m-2^n-th compoennt if e[n]=true, and do nothing otherwise
        for(m=GetSize()-1; m>=gsl_pow_int(2, n); m--){

            b[m].Replace(
                         //the element # m+2^n in b
                         &(b[m-gsl_pow_int(2, n)]),
                         //the element #n in e
                         &((e->b)[n])
                         );
        
            
        }
        
        //in this loop, I run over the second chunk of entries of b: m =2^n-1 , ..., 0. I can no longer replace b[m] with b[m-2^n] as in the loop above, becuase b[m-2^n] does not exist in b -> I replace it with zero. Note that if 2^n > b.size(), this second loop must cover the entire vector b -> I set as starting value of m  max(((int)(this->GetSize()))-((int)gsl_pow_int(2, n)), 0)
        for(m = min(((int)GetSize())-1, (((int)gsl_pow_int(2, n))-1)); m>=0; m--){
                     
            b[m].Replace(
                         //a Bits filled with zeros
                         &zero,
                         //the element #n in e
                         &((e->b)[n])
                         );
        
            
        }
        
    }
    
}


//return the position of the first signigificant bit in *this, starting from the last element of  b[]
inline UnsignedInt BitSet::PositionOfFirstSignificantBit(void){
    
    int s;
    Bits check_old, check_new, t, carry;
    //result must be big enough to host an unsigned int equal to this->GetSize()
    UnsignedInt result(GetSize());
    
    check_old.SetAll(0);
    result.SetAll(0);
    
    for(s=GetSize()-1; s>=0; s--){
        
        check_new = check_old | ((*this)[s]);
        t = (~check_new);
        result.AddTo(&t, &carry);
        
        check_old = check_new;
        
    }
    
    return result;

    
}


//speed test of UnsignedInt::AddTo method, with S samples and seed seed
inline void SpeedTestUnsignedIntAddto(unsigned long long int S, unsigned long long int seed){
    
    //test for speed for UnsignedInt +=
    
    
    cout << " ***************************** Speed test for UnsignedInt::AddTo *****************************" << endl;
    
    clock_t start=0, end=0;
    gsl_rng* ran;
    double dummy;
    unsigned int i;
    unsigned long long int s, r, MAX = 1024;
    Bits carry;

    vector<UnsignedInt> A(S), B(S);
    vector<unsigned int> a(S), b(S);


    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    gsl_rng_set(ran, seed);


    //****************** calculation without bits ******************
    start = clock();
    for(s=0; s<S; ++s){
        dummy = gsl_rng_uniform(ran);
    }
    end = clock();
    cout << "Time to draw S random numbers without bits = "  << std::scientific << ((double)(end - start))/CLOCKS_PER_SEC << " s" << endl;

    

    //****************** calculation without bits ******************
    for(s=0; s<S; s++){

            r = gsl_rng_uniform_int(ran, MAX);
            a[s] = (unsigned int)r;
            if(r!=0){
                b[s] = (unsigned int)(r-1-gsl_rng_uniform_int(ran, r));
            }else{
                b[s] = 0;
            }

    }
 

    start = clock();
    for(s=0; s<S; s++){

        //        (a[s]) += b[s];
        (a[s]) -= b[s];

    }
    end = clock();
    cout  << "Time for S operation without bits = "  << std::scientific << ((double)(end - start))/CLOCKS_PER_SEC << " s" << endl;


    //****************** calculation with bits ******************
    for(s=0; s<S; s++){

        A[s] = UnsignedInt(MAX);
        B[s] = UnsignedInt(MAX);

    }

    for(s=0; s<S; s++){

        for(i=0; i<n_bits; i++){

            r = gsl_rng_uniform_int(ran, MAX);
            A[s].Set(i, r);
            if(r!=0){
                B[s].Set(i, r-1-gsl_rng_uniform_int(ran, r));
            }else{
                B[s].Set(i, 0);
            }

        }

    }


    start = clock();
    for(s=0; s<S; s++){

        //        A[s].PrintBase10("A");
        //        B.PrintBase10("B");

        //        (A[s]) += (&B[s]);
        //        (A[s]).AddTo(&(B[s]), &carry);

        //                (A[s]) -= (&B[s]);
        (A[s]).SubstractTo(&(B[s]), &carry);




        //        A[s].PrintBase10("A");

    }
    end = clock();

    cout << "Time for S operations with bits = "   << std::scientific << ((double)(end - start))/CLOCKS_PER_SEC << "s" <<  endl << endl;


    //without this the for loop will not be exectued with -O3
    cout << endl;
    A.back().PrintBase10("dummy print");
    cout << "dummy print: a = " << a[S-1] << " " << b[S-1] << dummy << endl;
    
}
