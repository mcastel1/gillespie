//
//  lib.cpp
//  gillespie
//
//  Created by Michele on 13/02/2024.
//


#include "lib.hpp"

//this file includes functions that do not belong a classes

inline unsigned long long int two_pow(unsigned long long int i){
    
    return ((unsigned long long int)gsl_pow_int(2.0, ((int)i)));
    
}

//return the number of bits necessary to write n in base 2
unsigned int inline bits(unsigned long long int n){
    
    unsigned int s;
    
    for(s=0; two_pow(s) <= (unsigned long long int)n; s++){}
    
    return s;
    
}


//print bit-by-bit the double x
inline void bitwise_print_double(const double& x){
    
    uint8_t *bytePointer = (uint8_t*)&x;
    size_t index;
    uint8_t byte;
    int bit;
    unsigned int p;
    vector<bool> result(n_bits);
    
    for(index=0, p=0; index < sizeof(double); index++){
        
        byte = bytePointer[index];
        
        for(bit = 0; bit < 8; bit++, p++){
            
            result[p] = ((bool)(byte & 1));
            byte >>= 1;
            
        }
        
    }
    
    
    cout << "double:";
    for(p=0; p<n_bits; p++){
        
        switch (p) {
            case 0:
                cout << "\n\tSign: ";
                break;
                
            case 1:
                cout << "\n\tExponent: ";
                break;
                
            case 12:
                cout << "\n\tMantissa: ";
                break;
                
            default:
                break;
        }
        
        cout << result[n_bits-1-p];
        
    }
    
    cout << "\n";
    
    
}


//write the mantissa of x into *result by resizing *result properly. This method requires that result->size() = n_bits_mantissa
inline void GetMantissaFromDouble(vector<bool>* result, double x){
    
    uint64_t *pointer = (uint64_t*)&x;
    uint64_t byte;
    unsigned int p;
    
    
    byte = pointer[0];
    
    for(p=0; (p < 64) && (p < result->size());  p++){
        //run through the part of x which is the mantissa
        
        (*result)[p] = ((bool)(byte & 1));
        
        byte >>= 1;
        
    }
    
}




//    Fraction r(n_bits_mantissa);
//    UnsignedInt n(16), result;
//
//    result.Resize(r.GetSize()+n.GetSize());
//    r.SetRandom((unsigned int)0);
//    n.SetRandom((unsigned int)1);
//
//    r.PrintBase10("r");
//    n.PrintBase10("n");
//
//
//
//    r.FloorMultiply(&n, &result);
//
//    result.PrintBase10("result");


//test for Double::operator <
/*
 Double a, b;
 unsigned int s, i;
 gsl_rng* ran;
 Bits smaller;
 vector<double> v_a, v_b;
 bool it_works;
 
 
 ran = gsl_rng_alloc(gsl_rng_gfsr4);
 gsl_rng_set(ran, seed);
 
 
 for(it_works=true, s=0; s<1000; ++s){
 
 for(i=0; i<n_bits; i++){
 a.Set(i, false, 1023 + (128/2 - gsl_rng_uniform_int(ran, 128)), gsl_rng_uniform(ran));
 b.Set(i, false, 1023 + (128/2 - gsl_rng_uniform_int(ran, 128)), gsl_rng_uniform(ran));
 }
 
 a.GetBase10(v_a);
 b.GetBase10(v_b);
 
 cout << "a : " << endl;
 //    a.Print();
 a.PrintBase10();
 cout << "b : " << endl;
 //    b.Print();
 b.PrintBase10();
 smaller  = (a < b);
 cout << "a<b : " << endl;
 smaller.Print();
 
 
 
 for(i=0; i<n_bits; ++i){
 cout << "\t" << (v_a[i] < v_b[i]) << "\t" << smaller.Get(i) << endl;
 if((v_a[i] < v_b[i]) != smaller.Get(i)){it_works = false; break;}
 }
 
 }
 
 
 cout << "Check of the result:" << it_works << endl;
 */




//

//test for == for Unsigned Ints
/*
 UnsignedInt a(10), b(10);
 Bits check;
 a.SetRandom((unsigned int)0);
 b.SetRandom((unsigned int)3);
 cout << "a : " << endl;
 a.PrintBase10();
 cout << "b : " << endl;
 b.PrintBase10();
 
 
 check = (a == b);
 
 int x;
 x=0;
 cout <<  x;
 */


//test for <<= and >>=
/*
 BitSet n(80);
 UnsignedInt shift(12);
 n.SetRandom((unsigned int)0);
 shift.SetRandom((unsigned int)0);
 cout << "shift:" << endl;
 shift.PrintBase10();
 
 cout << "n before >>= :" << endl;
 n.Print();
 
 n >>= &shift;
 
 cout << "n after >>= :" << endl;
 n.Print();
 */


/*
 //test for Double::Normalize
 Double x;
 x.SetRandom((unsigned int)0);
 cout << "x before noramlize:";
 //    x.Print();
 x.PrintBase10();
 x.Normalize();
 cout << "x after noramlize:";
 x.PrintBase10();
 */


//
//test for UnsignedInt::Normalize
//    UnsignedInt x(10), one(1);



/*
 //test for Bits::Swap
 Bits a, b, check, w;
 a.SetRandom((unsigned int)0);
 b.SetRandom((unsigned int)1);
 check.SetRandom((unsigned int)2);
 
 a.Print("a");
 b.Print("b");
 check.Print("c");
 a.Swap(&b, check, &w);
 
 
 a.Print("a");
 b.Print("b");
 */

//test for BitSet::Swap
/*
 BitSet a(4), b(4);
 Bits check, w;
 a.SetRandom((unsigned int)0);
 b.SetRandom((unsigned int)1);
 check.SetRandom((unsigned int)2);
 
 a.Print("a");
 b.Print("b");
 check.Print("      c");
 
 a.Swap(&b, check, &w);
 
 
 a.Print("a");
 b.Print("b");
 
 */


//test for Double::Swap
/*
 Double a, b;
 Bits check, w;
 a.SetRandom((unsigned int)0);
 b.SetRandom((unsigned int)1);
 check.SetRandom((unsigned int)2);
 
 a.PrintBase10("a");
 b.PrintBase10("b");
 check.Print("      c");
 
 a.Swap(&b, check, &w);
 
 
 a.PrintBase10("a");
 b.PrintBase10("b");
 */
