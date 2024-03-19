//
//  system.cpp
//  gillespie
//
//  Created by Michele on 07/02/2024.
//

#include "system.hpp"

inline System_bits::System_bits(void){
    
}

inline System_bits::System_bits(unsigned long long int N_in, unsigned int seed_in){
    
    unsigned int i, s, *n, n_bits_R;
    const double p[] = {1.0, 1.0, 2.0};
    
    
    n = new unsigned int [3];
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    
    gsl_rng_set(ran, seed);
    
    N = N_in;
    seed = seed_in;
    
    
    //number of bits to write the random number (Fraction) R for the Gillespie simulation
    //VERIFY
    n_bits_R = bits((unsigned int)(gsl_pow_2(N)/3.0));
    //VERIFY
    
    for(x.clear(), /*c.clear(),*/ i=0; i<3; ++i){
        
        x.push_back(UnsignedInt(N));
        //        c.push_back(UnsignedInt(M));
        //a must host c[](x[]*x[], thus
        a.push_back(UnsignedInt(M*N*N));
        
    }
    
    A = UnsignedInt(N*N);
    //Z must contain a[0] + a[1] + a[2]
    Z = UnsignedInt(3*M*N*N);
    R = UnsignedInt(N*(N-1)/2);
    RHS.Resize(Z.GetSize());
    W.Resize(R.GetSize() + Z.GetSize());
    w.resize(n_bits_R);
    
    
    for(s=0; s<n_bits; s++){
        
        //draw the initial number of particles of the three species according to a multinomial distribution
        gsl_ran_multinomial(ran, 3, (unsigned int)N, p, n);
        
        for(i=0; i<3; ++i){
            
            //write the initial number of particles in x
            x[i].Set(s, n[i]);
            //draw the values of c and write them in c
            //            c[i].Set(s, gsl_rng_uniform_int(ran, M));
            
        }
        
    }
    
    
    //    for(i=0; i<3; ++i){
    //        
    //        cout << "c[" << i << "]" << endl;
    //        c[i].PrintBase10("");
    //        
    //    }
    //    
    //    
    //    for(i=0; i<3; ++i){
    //        
    //        cout << "x[" << i << "]" << endl;
    //        x[i].PrintBase10("");
    //        
    //    }
    
    delete [] n;
    
}

inline void System_bits::Iterate(void){
    
    //draw the random numbers
    R.SetAll(gsl_rng_uniform_int(ran, N*(N-1)/2));
    
    
    //    q = gsl_rng_uniform_int(ran, 3);
//
//    
//    //    c[0].PrintBase10("c[0]");
//    //    x[0].PrintBase10("x[0]");
//    //    x[1].PrintBase10("x[1]");
//    
//    
//    //THESE SHOULD BE OPTIMIZED BY UPDATING x[i] from the previous step with a sum 
//    /*
//     x[0].Multiply(&(x[1]), &A);
//     x[0].Multiply(&(x[2]), &A);
//     x[1].Multiply(&(x[2]), &A);
//     */
//    
//    //add the a[]s and compute Z
//    Z.BitSet::Set(&(a[0]));
//    Z.AddTo(&(a[1]), &carry);
//    Z.AddTo(&(a[2]), &carry);
//    
//    R.FloorMultiply(&Z, &RHS, &W);
//    
//    //    a[0].PrintBase10("c[0]*x[0]*x[1]");
    
}


inline System_nobits::System_nobits(void){
    
}


inline System_nobits::System_nobits(unsigned long long int N_in, unsigned int seed_in){
    
    unsigned int i, *n;
    const double p[] = {1.0, 1.0, 2.0};
    
    
    
    n = new unsigned int [3];
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    
    gsl_rng_set(ran, seed);
    
    N = N_in;
    seed = seed_in;
    
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


inline void System_nobits::iterate(void){
    
    //draw the random numbers
    r = gsl_rng_uniform(ran);
    q = gsl_rng_uniform_int(ran, 3);
    
    
    a[0] = x[0]*x[1];
    a[1] = x[0]*x[2];
    a[2] = x[1]*x[2];
    
    z = a[0]+a[1]+a[2];
    
    rhs = floor(r*z);
    
    
}
