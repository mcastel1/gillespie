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



inline void UnsignedInt::PrintBase10(string title){
    
    PrintBase10(title, cout);
    
}


inline void UnsignedInt::PrintBase10(const string& title, ostream& output_stream){
    
    unsigned int  p;
    vector<unsigned long long int> v;
    
    output_stream << title << ": {";
    for(p=0, GetBase10(v); p<n_bits; p++){
        output_stream << v[n_bits-1-p] << "\t";
    }
    output_stream << "}" << endl;

    
}


inline void UnsignedInt::GetBase10(vector<unsigned long long int>& v){
    
    unsigned int p;
    for(p=0, v.resize(n_bits); p<n_bits; p++){
        
        v[p] = Get(p);
        
    }
    
}


inline void UnsignedInt::operator = (BitSet m){
    
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
        for(m = max(((int)GetSize())-((int)gsl_pow_int(2, n)), 0); (m<((int)GetSize())); m++){
            
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
inline void SpeedTestUnsignedIntAddto(unsigned long long int maximum_value, unsigned long long int S, unsigned long long int seed){
        
    
    cout << " ***************************** Speed test for UnsignedInt::AddTo *****************************" << endl;
    
    clock_t start=0, end=0;
    gsl_rng* ran;
    unsigned int i;
    unsigned long long int s, r=0;
    double x = 0.0;
    Bits carry;
    
    vector<UnsignedInt> A(S), B(S);
    vector<unsigned int> a(n_bits*S), b(n_bits*S);
    
    
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    gsl_rng_set(ran, seed);
    
    
    //****************** calculation without bits ******************
    for(s=0; s<n_bits*S; s++){
        
        r = gsl_rng_uniform_int(ran, maximum_value);
        a[s] = (unsigned int)r;
        if(r!=0){
            b[s] = (unsigned int)(r-1-gsl_rng_uniform_int(ran, r));
        }else{
            b[s] = 0;
        }
        
    }
    
    
    start = clock();
    for(s=0; s<n_bits*S; s++){
        
        //this simulates the drawing of the random number for the Gillespie algorithm
        r = gsl_rng_uniform_int(ran, maximum_value);
        x = gsl_rng_uniform(ran);
        //        (a[s]) += b[s];
        (a[s]) -= b[s];
        
    }
    end = clock();
    cout  << "Time for n_bits*S [random number + operation]s without bits = "  << std::scientific << ((double)(end - start))/CLOCKS_PER_SEC << " s" << endl;
    
    
    //****************** calculation with bits ******************
    for(s=0; s<S; s++){
        
        A[s] = UnsignedInt(maximum_value);
        B[s] = UnsignedInt(maximum_value);
        
    }
    
    for(s=0; s<S; s++){
        
        for(i=0; i<n_bits; i++){
            
            r = gsl_rng_uniform_int(ran, maximum_value);
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
        
        //this simulates the drawing of the random number for the Gillespie algorithm
        r = gsl_rng_uniform_int(ran, maximum_value);
        x = gsl_rng_uniform(ran);
        //        (A[s]) += (&B[s]);
        //        (A[s]).AddTo(&(B[s]), &carry);
    //                (A[s]) -= (&B[s]);
        (A[s]).SubstractTo(&(B[s]), &carry);
        
        //        A[s].PrintBase10("A");
        
    }
    end = clock();
    
    cout << "Time for S [random number + operation]s with bits = " << std::scientific << ((double)(end - start))/CLOCKS_PER_SEC << "s" <<  endl << endl;
    
    
    //without this the for loop will not be exectued with -O3
    cout << endl;
    A.back().PrintBase10("dummy print");
    cout << "dummy print: a = " << a[S-1] << " " << b[S-1] << r << x << endl;
    
}


//test for BitSet::AddTo/SubstractTo
inline void TestUnsignedIntAddTo(unsigned long long int S, unsigned long long int seed){
    
    UnsignedInt a, b;
    vector<unsigned long long int> v_a, v_b, v_a_minus_b;
    unsigned int i, s;
    unsigned long long int r, MAX = 1024;
    gsl_rng* ran;
    Bits borrow;
    bool it_works;
    
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    gsl_rng_set(ran, seed);
    
    a.Resize(10);
    b.Resize(10);
    
    
    for(it_works = true, s=0; s<S; ++s){
        
        
        for(i=0; i<n_bits; i++){
            
            r = gsl_rng_uniform_int(ran, MAX);
            a.Set(i, r);
            if(r!=0){
                b.Set(i, r-1-gsl_rng_uniform_int(ran, r));
            }else{
                b.Set(i, 0);
            }
            
        }
        
        
        //        a.PrintBase10("a");
        //        b.PrintBase10("b");
        
        a.GetBase10(v_a);
        b.GetBase10(v_b);
        
        a.SubstractTo(&b, &borrow);
        
        //            a.PrintBase10("a-b");
        
        a.GetBase10(v_a_minus_b);
        
        for(i=0; i<n_bits; ++i){
            if( v_a[i]-v_b[i] !=  v_a_minus_b[i] ){
                it_works = false;
                break;
            }
            
            cout << "[" << i << "]:\t\t\t" << v_a[i]-v_b[i] << "\t\t\t" << v_a_minus_b[i] << endl;
        }
        //
        
    }
    
    cout << "It works = " << it_works << "." <<  endl;
    
    
}




//test for    UnsignedInt *=
inline void TestUnsignedIntMultiply(unsigned long long int S, unsigned long long int seed){
    
    //the maximum unsigned int that I will draw
    unsigned long long int max = 30;
    UnsignedInt A(max), B(max), C;
    bool it_works;
    vector<unsigned long long int> v_a, v_b, v_a_times_b;
    unsigned int i, s;
    gsl_rng* ran;
    
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    gsl_rng_set(ran, seed);
    
    
    for(it_works = true, s=0; (s<S) & it_works; ++s){
        
        A.Resize(0);
        B.Resize(0);
        
        A.Resize(bits(max));
        B.Resize(bits(max));
        C.Resize(A.GetSize()+B.GetSize());

        A.Clear();
        B.Clear();
        
        
        for(i=0; i<n_bits; i++){
            A.Set(i, gsl_rng_uniform_int(ran, max));
            B.Set(i, gsl_rng_uniform_int(ran, max));
        }
        
        
        //    cout << "----------- Before += -----------" << endl;
        //    cout << "a : " << endl;
        //    a.Print();
        //    a.PrintBase10();
        
        //    cout << "b : " << endl;
        //    b.Print();
        //    b.PrintBase10();
        
        A.GetBase10(v_a);
        B.GetBase10(v_b);
        
//        A *= &B;
        A.Multiply(&B, &C);
        
        //    cout << "----------- After += -----------" << endl;
        //    cout << "a+b: " << endl;
        //    a.Print();
        //    a.PrintBase10();
        
        C.GetBase10(v_a_times_b);
        
        cout << "Check of the result:" << endl;
        for( i=0; i<n_bits; ++i){

            cout << "[" << n_bits-1-i << "]:\t\t\t" << v_a[n_bits-1-i]*v_b[n_bits-1-i] << "\t\t\t" << v_a_times_b[n_bits-1-i] << endl;

            if(v_a[n_bits-1-i]*v_b[n_bits-1-i] != v_a_times_b[n_bits-1-i]){
                it_works = false;
                break;
            }
            
        }
        //
        
    }
    
    cout << "It works  = " << it_works << "." << endl;
    
    
}



inline void SpeedTestUnsignedIntMultiply(unsigned long long int maximum_value, unsigned long long int S, unsigned long long int seed){
    
    
    cout << " ***************************** Speed test for UnsignedInt::Multiply *****************************" << endl;

    
    clock_t start=0, end=0;
    gsl_rng* ran;
    unsigned long long int r=0, s;
    unsigned int i, b, c=0;
    double x = 0.0;
    
    vector<UnsignedInt> A(S);
    UnsignedInt B, C;
    vector<unsigned int> a(n_bits*S);
    
    for(s=0; s<A.size(); ++s){
        A[s].Resize(bits(maximum_value));
    }
    B.Resize(bits(maximum_value));
    C.Resize(A[0].GetSize()+B.GetSize());
    
    
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    gsl_rng_set(ran, seed);
    
    
    
    b = (unsigned int)gsl_rng_uniform_int(ran, maximum_value);
    //    cout << "b: " << b << endl;

    start = clock();
    for(s=0; s<n_bits*S; s++){
        
        //this simulates the drawing of the random number for the Gillespie algorithm
        r = gsl_rng_uniform_int(ran, maximum_value);
        x = gsl_rng_uniform(ran);
        c = (a[s]) * b;
        
    }
    end = clock();
    cout << "Time for n_bits * S [random number + operation]s without bits = "  << std::scientific << ((double)(end - start))/CLOCKS_PER_SEC << " s" << endl;
    
    
    //****************** calculation with bits ******************
    for(s=0; s<S; s++){
        
        for(i=0; i<n_bits; i++){
            A[s].Set(i, gsl_rng_uniform_int(ran, maximum_value));
        }
        
    }
    for(i=0; i<n_bits; i++){
        B.Set(i, gsl_rng_uniform_int(ran, maximum_value));
    }

    
    start = clock();
    for(s=0; s<S; s++){
        
        //        A[s].PrintBase10("A");
        //        B.PrintBase10("B");
        
        //        (A[s]) += (&B[s]);
        //        (A[s]).AddTo(&(B[s]), &carry);
        
        //                (A[s]) -= (&B[s]);
        //this simulates the drawing of the random number for the Gillespie algorithm
        r = (unsigned int)gsl_rng_uniform_int(ran, maximum_value);
        x = gsl_rng_uniform(ran);
        (A[s]).Multiply(&B, &C);
        
        //        A[s].PrintBase10("A");
        
    }
    end = clock();
    
    cout << "Time for S [random number + operation]s with bits = "   << std::scientific << ((double)(end - start))/CLOCKS_PER_SEC << "s" <<  endl << endl;
    
    
    
    //without this the for loop will not be exectued with -O3
    cout << endl;
    C.PrintBase10("dummy print");
    cout << "dummy print a = " << a[S-1] << " " << c << " " << r << x << endl;
    
    
    
}




/*multiply *this by *multiplicand and write the result in *result

 
 result->GetSize() <= (this-GetSize()) + (multiplicand->GetSize(), and when I call this method I take result->GetSize() = (this-GetSize()) + (multiplicand->GetSize() to be safe. Thus when this method is called, result->GetSize() must be equal to (this-GetSize()) + (multiplicand->GetSize()

 the times are from  ./main.o -s 0 -S 6
 */
inline void BitSet::Multiply(UnsignedInt* multiplicand, UnsignedInt* result){
    
    unsigned int s, p;
    Bits carry, t, u;
        
    
    for(s=0, result->SetAll(Bits_zero); s<multiplicand->GetSize(); s++){
        //multiply by the s-th element of multiplicand: at each step of this loop *this is shifted by s places to the left and added to the result
        
        for(p=0, carry.Clear(); p<GetSize(); p++){
            
            (u.n) = ((((*multiplicand)[s]).n) & ((b[p]).n));
            (t.n) = ((((result->b)[p+s]).n) ^ (u.n) ^ (carry.n));
            
            (carry.n) = ((u.n) & ((((result->b)[p+s]).n) | (carry.n))) | ((((result->b)[p+s]).n) & (carry.n));
            ((result->b)[p+s]).n = (t.n);
            
        }
        ((result->b)[p+s]).n = (carry.n);

    }
    
}

//this method requires *this to be even, it divides *this by 2 and writes the result in *this
inline void BitSet::DivideByTwoTo(void){
    
    //to divide by two, I shift all entries to the right by one place
    (*this) >>= (&Bits_one);
    
    
}

//this method  multiplies *this by 2 and writes the result in *this
inline void BitSet::MultiplyByTwoTo(void){
    
    //to divide by two, I shift all entries to the right by one place
    (*this) <<= (&Bits_one);
    
    
}


//compute the floor of *this x *multiplicant and store the result in *result. This requires result->GetSize() = multiplicand->GetSize() and work_space->GetSize() = (this->GetSize()) + (multiplicand->GetSize()) 
inline void Fraction::FloorMultiply(UnsignedInt* multiplicand, UnsignedInt* result, UnsignedInt* work_space){
    
    Multiply(multiplicand, work_space);
  
    //copy the last multiplicand->GetSize() bits of work_space into *result : this will yield the floor of the multiplication above
    copy(work_space->b.begin()+GetSize(), work_space->b.end(), result->b.begin());
     
}



//test for   Fraction::FloorMultiply
inline void TestFractionFloorMultiply(unsigned long long int S, unsigned long long int seed){
    
    //the maximum unsigned int that I will draw
    unsigned long long int max = 1024;
    UnsignedInt B(max), C, W;
    Fraction A;
    bool it_works;
    vector<unsigned long long int> v_A, v_floor_A_times_B;
    vector<double> v_B;
    unsigned int i, s;
    gsl_rng* ran;
    
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    gsl_rng_set(ran, seed);
    

    for(it_works = true, s=0; (s<S) & it_works; ++s){
        
        A.Resize(bits(n_bits_mantissa));
        B.Resize(bits(max));
        C.Resize(B.GetSize());
        W.Resize(A.GetSize() + B.GetSize());

        A.Clear();
        B.Clear();
        
        for(i=0; i<n_bits; i++){
            B.Set(i, gsl_rng_uniform_int(ran, max));
        }
        A.SetRandom(ran);
        
            
        A.GetBase10(&v_B);
        B.GetBase10(v_A);
        
        A.FloorMultiply(&B, &C, &W);
        
        C.GetBase10(v_floor_A_times_B);
        
        cout << "Check of the result:" << endl;
        for( i=0; i<n_bits; ++i){

            cout << "[" << n_bits-1-i << "]:\t\t\t" << floor(v_A[n_bits-1-i]*v_B[n_bits-1-i]) << "\t\t\t" << v_floor_A_times_B[n_bits-1-i] << endl;

            if(floor(v_A[n_bits-1-i]*v_B[n_bits-1-i]) != v_floor_A_times_B[n_bits-1-i]){
                it_works = false;
                break;
            }
            
        }
        //
        
    }
    
    cout << "It works  = " << it_works << "." << endl;
    
    
}



inline void SpeedTestFractionFloorMultiply(unsigned int n_bits_factor, unsigned long long int maximum_value_multiplicand, unsigned long long int S, unsigned long long int seed){
    
    
    cout << " ***************************** Speed test for Fraction::FloorMultiply *****************************" << endl;

    
  
    //the maximum unsigned int that I will draw
    unsigned long long int r=0;
    vector<double> a(n_bits*S);
    vector<Fraction> A(S);
    UnsignedInt B(maximum_value_multiplicand), C(maximum_value_multiplicand), W;
    unsigned int b=0, c=0, i, s;
    double x = 0.0;
    gsl_rng* ran;
    clock_t start=0, end=0;

    
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    gsl_rng_set(ran, seed);
    
    
    //****************** calculation without bits ******************
    b = (unsigned int)gsl_rng_uniform_int(ran, maximum_value_multiplicand);
    for(s=0; s<n_bits*S; s++){
        a[s] = gsl_rng_uniform(ran);
    }
    
    start = clock();
    for(s=0; s<n_bits*S; s++){
        
        //this simulates the drawing of the random number for the Gillespie algorithm
        r = gsl_rng_uniform_int(ran, maximum_value_multiplicand);
        x = gsl_rng_uniform(ran);
        
        c = floor((a[s])*b);
        
    }
    end = clock();
    cout  << "Time for n_bits*S [random number + operation]s without bits = "  << std::scientific << ((double)(end - start))/CLOCKS_PER_SEC << " s" << endl;
    

    
    
    //****************** calculation with bits ******************
    for(s=0; s<S; s++){
        A[s].Resize(n_bits_factor);

        A[s].SetRandom(ran);
    }
    for(i=0; i<n_bits; i++){
        B.Set(i, gsl_rng_uniform_int(ran, maximum_value_multiplicand));
    }
    W.Resize(A.front().GetSize() + B.GetSize());
    
    start = clock();
    for(s=0; s<S; ++s){
                
         //this simulates the drawing of the random number for the Gillespie algorithm
         r = gsl_rng_uniform_int(ran, maximum_value_multiplicand);
         x = gsl_rng_uniform(ran);

        A[s].FloorMultiply(&B, &C, &W);
        
    }
    end = clock();
    
    cout << "Time for S [random number + operation]s with bits = " << std::scientific << ((double)(end - start))/CLOCKS_PER_SEC << "s" <<  endl << endl;
    
    
    //without this the for loop will not be exectued with -O3
    cout << endl;
    A.back().PrintBase10("dummy print");
    C.PrintBase10("dummy print");
    cout << "dummy print: a = " << a.back() << " " << b << c << r << x << endl;
 

    
}