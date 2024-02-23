#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <fstream>
#include <strstream>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <list>
#include <stdio.h>
#include <time.h>
#include <getopt.h>

#include "gsl_rng.h"
#include "gsl_math.h"
#include "gsl_sf_log.h"

/*compile on mac
 //compile without optimization
 g++ main.cpp -llapack -lgsl -lcblas -lm -O0 -Wno-deprecated -I ./ -I/usr/local/include/gsl/ -o main.o -Wall -DHAVE_INLINE
 
 //compile with optimization
 g++ main.cpp -llapack -lgsl -lcblas -lm -O3 -Wno-deprecated -I ./ -I/usr/local/include/gsl/ -o main.o -Wall -DHAVE_INLINE
 
 ./main.o -N 1 -s 0 -S 1024
 */

/*
 note: - the performance test is very different if you do it on Xcode or on command line with -O3
  - to circumvent the slow down with >>= in Double::AddTo, represent a Double as a BitSet, where the first bs represent the mantissa and the others the part > 1
 */



#include "main.hpp"
#include "lib.cpp"
#include "bits.cpp"
#include "bitset.cpp"


#include "int.cpp"
#include "unsigned_int.cpp"
#include "double.cpp"
#include "system.cpp"

//all entries of BitSet_one are equal to 1


/*
 void UnsignedInt::SetRandom(unsigned long long int seed){
 
 int i;
 gsl_rng* ran;
 
 ran = gsl_rng_alloc(gsl_rng_gfsr4);
 gsl_rng_set(ran, seed);
 
 
 for(i=0; i<b.size(); i++){
 
 
 }
 
 }
 */



int main(int argc, char * argv[]) {
    
    cout.precision(cout_precision);
    BitSet_one.ResizeAndSetAll(1);
    Bits_one.SetAll(true);
    Bits_zero.SetAll(false);
    
    int options;
    unsigned long long int seed=0/*, N=0*/, S=0;
    
    while ((options = getopt(argc, argv, ":S:s:")) != -1) {
        
        switch (options) {
                
                //                case 'N':
                //                    N = ((unsigned int)atoi(optarg));
                //                    break;
                
            case 's':
                seed = ((unsigned int)atoi(optarg));
                break;
                
            case 'S':
                S = ((unsigned int)gsl_pow_int(10, atoi(optarg)));
                break;
                
                
        }
        
    }
    
    
    
    
    
    
    
    //    CorrectnessTestDoubleAddTo(S, seed);
    SpeedTestDoubleAddTo(S, seed);
    //    SpeedTestUnsignedIntAddto(S, seed);
    
    
    
    
    
    
    
    
    ////speed test for BitSet::operator -=
    //    //
    //    vector<UnsignedInt> a(S);
    //    UnsignedInt b(16);
    //    unsigned int s;
    //    clock_t start=0, end=0;
    //    Bits borrow;
    //
    //    b.SetRandom((unsigned int)0);
    //    for(s=0; s<S; ++s){
    //
    //
    //        a[s].Resize(16);
    //        a[s].SetRandom(s);
    //
    //        //        a[s].PrintBase10("a");
    //        //        b.PrintBase10("b");
    //
    //        //        a[s].PrintBase10("a+b");
    //    }
    //
    //    start = clock();
    //    for(s=0; s<S; ++s){
    //        a[s].SubstractTo(&b, &borrow);
    ////                a[s] -= (&b);
    //    }
    //    end = clock();
    //    cout << endl << endl  << "Time with bits = "  << std::scientific << ((double)(end - start))/CLOCKS_PER_SEC << " s" << endl << endl;
    //
    //    a.back().PrintBase10("dummy");
    
    
    //     //test for BitSet::SubstractTo
    //
    //    UnsignedInt a, b;
    //    vector<unsigned long long int> v_a, v_b, v_a_minus_b;
    //    unsigned int i, s;
    //    unsigned long long int r, MAX = 1024;
    //    gsl_rng* ran;
    //    Bits borrow;
    //    bool it_works;
    //
    //    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    //    gsl_rng_set(ran, seed);
    //
    //    a.Resize(10);
    //    b.Resize(10);
    //
    //
    //    for(it_works = true, s=0; s<S; ++s){
    //
    //
    //        for(i=0; i<n_bits; i++){
    //
    //            r = gsl_rng_uniform_int(ran, MAX);
    //            a.Set(i, r);
    //            if(r!=0){
    //                b.Set(i, r-1-gsl_rng_uniform_int(ran, r));
    //            }else{
    //                b.Set(i, 0);
    //            }
    //
    //        }
    //
    //
    ////        a.PrintBase10("a");
    ////        b.PrintBase10("b");
    //
    //        a.GetBase10(v_a);
    //        b.GetBase10(v_b);
    //
    //        a.SubstractTo(&b, &borrow);
    //
    ////            a.PrintBase10("a-b");
    //
    //        a.GetBase10(v_a_minus_b);
    //
    //        for(i=0; i<n_bits; ++i){
    //            if( v_a[i]-v_b[i] !=  v_a_minus_b[i] ){
    //                it_works = false;
    //                break;
    //            }
    //
    //            cout << "[" << i << "]:\t\t\t" << v_a[i]-v_b[i] << "\t\t\t" << v_a_minus_b[i] << endl;
    //        }
    //        //
    //
    //    }
    //
    //    cout << "It works = " << it_works << "." <<  endl;
    
    
    
    
    
    
    
    
    
    
    
    
    
    //test for    UnsignedInt *=
    /*
     unsigned long long int max =1000;
     UnsignedInt a(max), b(max);
     double it_works;
     vector<unsigned long long int> v_a, v_b, v_a_times_b;
     unsigned int i, s;
     gsl_rng* ran;
     
     ran = gsl_rng_alloc(gsl_rng_gfsr4);
     gsl_rng_set(ran, seed);
     
     
     for(it_works = true, s=0; s<1000; ++s){
     
     a.Resize(0);
     b.Resize(0);
     
     a.Resize(bits(max));
     b.Resize(bits(max));
     
     a.Clear();
     b.Clear();
     
     
     for(i=0; i<n_bits; i++){
     a.Set(i, gsl_rng_uniform_int(ran, max));
     b.Set(i, gsl_rng_uniform_int(ran, max));
     }
     
     
     //    cout << "----------- Before += -----------" << endl;
     //    cout << "a : " << endl;
     //    a.Print();
     //    a.PrintBase10();
     
     //    cout << "b : " << endl;
     //    b.Print();
     //    b.PrintBase10();
     
     a.GetBase10(v_a);
     b.GetBase10(v_b);
     
     a *= &b;
     
     //    cout << "----------- After += -----------" << endl;
     //    cout << "a+b: " << endl;
     //    a.Print();
     //    a.PrintBase10();
     
     a.GetBase10(v_a_times_b);
     
     cout << "Check of the result:" << endl;
     for( i=0; i<n_bits; ++i){
     if(v_a[n_bits-1-i]*v_b[n_bits-1-i] != v_a_times_b[n_bits-1-i]){it_works = false;}
     
     cout << "[" << n_bits-1-i << "]:\t\t\t" << v_a[n_bits-1-i]*v_b[n_bits-1-i] << "\t\t\t" << v_a_times_b[n_bits-1-i] << endl;
     }
     //
     
     }
     
     cout << "It works  = " << it_works << "." << endl;
     */
    
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
    
    
    //test for BitSet::+=
    /*
     x.SetRandom((unsigned int)0);
     one.SetAll(1);
     
     cout << "x before +=:";
     x.Print();
     x.PrintBase10();
     
     x += &one;
     x += &one;
     
     cout << "x after +=:";
     x.Print();
     x.PrintBase10();
     */
    
    
    //
    
    //test for    Double +=
    /*
     Double a, b;
     double error;
     vector<double> v_a, v_b, v_a_plus_b;
     unsigned int i, s;
     gsl_rng* ran;
     
     ran = gsl_rng_alloc(gsl_rng_gfsr4);
     gsl_rng_set(ran, seed);
     
     
     for(error = 0.0, s=0; s<100; ++s){
     
     for(i=0; i<n_bits; i++){
     a.Set(i, false, 1023 + (128/2 - gsl_rng_uniform_int(ran, 128)), gsl_rng_uniform(ran));
     b.Set(i, false, 1023 + (128/2 - gsl_rng_uniform_int(ran, 128)), gsl_rng_uniform(ran));
     }
     
     
     //    cout << "----------- Before += -----------" << endl;
     //    cout << "a : " << endl;
     //    a.Print();
     //    a.PrintBase10();
     
     //    cout << "b : " << endl;
     //    b.Print();
     //    b.PrintBase10();
     
     a.GetBase10(v_a);
     b.GetBase10(v_b);
     
     a+=b;
     
     //    cout << "----------- After += -----------" << endl;
     //    cout << "a+b: " << endl;
     //    a.Print();
     //    a.PrintBase10();
     
     a.GetBase10(v_a_plus_b);
     
     cout << "Check of the result:" << endl;
     for( i=0; i<n_bits; ++i){
     if(fabs(((v_a[n_bits-1-i]+v_b[n_bits-1-i])-v_a_plus_b[n_bits-1-i])/v_a_plus_b[n_bits-1-i]) > error){error = fabs(((v_a[n_bits-1-i]+v_b[n_bits-1-i])-v_a_plus_b[n_bits-1-i])/v_a_plus_b[n_bits-1-i]);}
     
     cout << "[" << n_bits-1-i << "]:\t\t\t" << v_a[n_bits-1-i]+v_b[n_bits-1-i] << "\t\t\t" << v_a_plus_b[n_bits-1-i] << "\t\t\t" << fabs(((v_a[n_bits-1-i]+v_b[n_bits-1-i])-v_a_plus_b[n_bits-1-i])/v_a_plus_b[n_bits-1-i]) << endl;
     }
     //
     
     }
     
     cout << "Maximum relative error = " << error << endl;
     */
    
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
    
    
    cout << endl;
    return 0;
    
}
