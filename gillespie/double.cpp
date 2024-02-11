//
//  double.cpp
//  gillespie
//
//  Created by Michele on 10/02/2024.
//

#include "double.hpp"

//default constructor
inline Double::Double(void){
    
    b.resize(54);
    e.resize(11);
    
}

//set the fraction to zero, the exponent to 1023 and the sign to +
inline void Double::Clear(){
    
    unsigned int p;
    
    //set the fraction to zero
    for(p=0; p<b.size(); p++){
        (b[p]).n = 0;
    }
    
    //set the exponent to 1023
    for(p=0; p<e.size()-1; p++){
        (e[p]).SetAll(true);
    }
    e.back().SetAll(false);
    
    //set the sign to +
    s.SetAll(false);
    
}


//initialize *this randomly with seed seed
inline void Double::SetRandom(unsigned int seed){
    
    unsigned int i;
    gsl_rng* ran;
    
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    gsl_rng_set(ran, seed);
    
    
    for(i=0; i<b.size(); i++){
        b[i].SetRandom(ran);
    }
    for(i=0; i<e.size(); i++){
        e[i].SetRandom(ran);
    }
    s = (bool)gsl_rng_uniform_int(ran, 2);
    
    gsl_rng_free(ran);

}


void Double::Print(void){
    
    unsigned int i;
    
    cout << "\n";
    for(i=0; i<b.size(); i++){
        cout << "b[" << i << "] = ";
        b[i].Print();
    }
    cout << "\n";
    for(i=0; i<e.size(); i++){
        cout << "e[" << i << "] = ";
        e[i].Print();
    }
    cout << "\n";
    s.Print();
    
}

//print *this in base 10
void Double::PrintBase10(void){
    
    unsigned int i, p;
    double b_10, e_10/*, A*/;
//    bool B;
    
    cout << "Double in base 10: {";
    for(p=0; p<n_bits; p++){
        
        for(b_10=1.0, i=0; i<b.size(); i++){
//            A = gsl_pow_int(2.0, -(i+1));
//            B = (b[b.size()-1-i].Get(p));
            b_10 += gsl_pow_int(2.0, -(i+1)) * (b[b.size()-1-i].Get(p));
        }
        for(e_10=-1023.0, i=0; i<e.size(); i++){
            e_10 += two_pow(i) * (e[i].Get(p));
        }
    
        cout << gsl_pow_int(-1.0, s.Get(p)) * gsl_pow_int(2.0, e_10) * b_10 << " ";
        
    }
    
    cout << "}\n";
        
}
