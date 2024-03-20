//
//  system.cpp
//  gillespie
//
//  Created by Michele on 07/02/2024.
//

#include "system.hpp"

inline SystemBits::SystemBits(void){
    
}

inline SystemBits::SystemBits(unsigned long long int N_in, unsigned int seed_in){
    
    
    unsigned int i, s, *n, n_bits_R;
    const double p[] = {1.0, 1.0, 2.0};
    
    
    n = new unsigned int [3];
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    
    gsl_rng_set(ran, seed);
    
    N = N_in;
    seed = seed_in;
    N_N_m_1_2 = N*(N-1)/2;

    
    //number of bits to write the random number (Fraction) R for the Gillespie simulation
    //VERIFY
    n_bits_R = bits((unsigned int)(gsl_pow_2(N)/3.0));
    //VERIFY
    
    for(x.clear(), /*c.clear(),*/ i=0; i<3; ++i){
        x.push_back(UnsignedInt(N));
    }
    
    //set a[i] so they can host the maximum values that can be stored in them
    //double check
    for(a.resize(6), i=0; i<3; i++){
        a[i] = UnsignedInt(gsl_pow_2(N/2));
        a[3+i] = UnsignedInt(N*(N-1)/2);
    }
    //double check
    


    L = UnsignedInt(N*(N-1)/2);
    R = UnsignedInt(N*(N-1)/2);
    w.resize(n_bits_R);
    
    //set x
    for(s=0; s<n_bits; s++){
        
        //draw the initial number of particles of the three species according to a multinomial distribution
        gsl_ran_multinomial(ran, 3, (unsigned int)N, p, n);
        
        for(i=0; i<3; ++i){
            
            //write the initial number of particles in x
            x[i].Set(s, n[i]);
              
        }
        
    }
    
//    x[0] -> A, x[1] -> L, x[2] -> D*
    
    //set a
    //set the first three values of a
    x[0].Multiply(&(x[2]), &(a[0]));
    x[0].Multiply(&(x[1]), &(a[1]));
    x[1].Multiply(&(x[2]), &(a[2]));
    
    //set the last three values
    x[0].Multiply(&(x[0]), &(a[3]));
    a[3].SubstractTo(&(x[0]), &borrow);
    a[3].DivideByTwoTo();

    x[2].Multiply(&(x[2]), &(a[4]));
    a[4].SubstractTo(&(x[2]), &borrow);
    a[4].DivideByTwoTo();

    x[1].Multiply(&(x[1]), &(a[5]));
    a[5].SubstractTo(&(x[1]), &borrow);
    a[5].DivideByTwoTo();


//
//    for(cout << "x[]: " << endl, i=0; i<x.size(); ++i){
//        cout << "x[" << i << "]" << endl;
//        x[i].PrintBase10("");
//    }
//    
//    
//    for(cout << "a[]:" << endl, i=0; i<a.size(); ++i){
//        cout << "a[" << i << "]" << endl;
//        a[i].PrintBase10("");
//    }

    
    delete [] n;
    
}

inline void SystemBits::Iterate(void){
    
    unsigned int i;
    
    //draw the random numbers
    r1 = gsl_rng_uniform(ran);
    //the SetAll command here is a bottleneck
    R.SetAll(gsl_rng_uniform_int(ran, N_N_m_1_2));
    //the SetAll command here is a bottleneck

    /*
     a0 = sum_{ a < b} x_a x_b + sum_a x_a(x_a-1)/2
        = 1/2 sum_{a!=b} x_a x_b + sum_a x_a(x_a-1)/2
        = 1/2 sum_{a!=b} x_a x_b + 1/2 sum_a x_a x_a - N/2
        = 1/2 sum_{a,b} x_a x_b - N/2
        = N^2/2 - N/2
        = N(N-1)/2
     */
    
    R.PrintBase10("R");
    
    
//    for(cout << "x[]: " << endl, i=0; i<x.size(); ++i){
//        cout << "x[" << i << "]" << endl;
//        x[i].PrintBase10("");
//    }
    
    
    for(cout << "a[]:" << endl, i=0; i<a.size(); ++i){
        cout << "a[" << i << "]" << endl;
        a[i].PrintBase10("");
    }
    
    //run through all reactions and compute the left-hand size of eq. (10b) in gillespie2007stochastic
    for (L.SetAll(0), compare_old.SetAll(true), i=0; i<6; i++) {
        
        
        L.AddTo(&(a[i]), &carry);

        compare_new = (L < R);
        changer = (compare_old ^ compare_new);
        
        L.PrintBase10("L");
        compare_old.Print("compare_old");
        compare_new.Print("compare_new");
        changer.Print("changer");
        
        compare_old = compare_new;

    }
    

    
    

    
}


inline systemnobits::systemnobits(void){
    
}


inline systemnobits::systemnobits(unsigned long long int N_in, unsigned int seed_in){
    
    unsigned int i, *n;
    const double p[] = {1.0, 1.0, 2.0};
    
    
    
    n = new unsigned int [3];
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    
    gsl_rng_set(ran, seed);
    
    N = N_in;
    seed = seed_in;
    N_N_m_1_2 = N*(N-1)/2;
    
    x.resize(3);
    //    c.resize(3);
    a.resize(3);
    
    
    
    //draw the initial number of particles of the three species according to a multinomial distribution
    gsl_ran_multinomial(ran, 3, (unsigned int)N, p, n);
    
    for(i=0; i<3; ++i){
        
        //write the initial number of particles in x
        x[i] = n[i];
        //draw the values of c and write them in c
        //        c[i] = (unsigned int)gsl_rng_uniform_int(ran, M);
        
    }
    
    delete [] n;
    
}


inline void systemnobits::iterate(void){
    
    //draw the random numbers
    r1 = gsl_rng_uniform(ran);
    R = gsl_rng_uniform_int(ran, N_N_m_1_2);
    
    
//    a[0] = x[0]*x[1];
//    a[1] = x[0]*x[2];
//    a[2] = x[1]*x[2];
//    
//    z = a[0]+a[1]+a[2];
//    
//    rhs = floor(r1*z);
    
    
}
