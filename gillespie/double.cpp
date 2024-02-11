//
//  double.cpp
//  gillespie
//
//  Created by Michele on 10/02/2024.
//

#include "double.hpp"

//default constructor
inline Double::Double(void){
    
    b.resize(52);
    e.Resize(11);
    
}

//set the fraction to zero, the exponent to 1023 and the sign to +
inline void Double::Clear(){
    
    unsigned int p;
    
    //set the fraction to zero
    for(p=0; p<b.size(); p++){
        (b[p]).n = 0;
    }
    
    //set the exponent to 1023
    for(p=0; p<e.GetSize()-1; p++){
        (e[p]).SetAll(true);
    }
    e.b.back().SetAll(false);
    
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
    for(i=0; i<e.GetSize(); i++){
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
    for(i=0; i<e.GetSize(); i++){
        cout << "e[" << i << "] = ";
        e[i].Print();
    }
    cout << "\ns = ";
    s.Print();
    
}



//set all entries of *this according to the double x
inline void Double::SetAllVertically(double x){
//
//    //set the exponent
//    //x = (-1)^s * 2^(e-1023) * (1+ ....).
//    //log_2|x| = e-1023 + log(1+...)
//    //integer_part(log_2|x|) = e-1023
//    e.SetAll(floor(gsl_sf_log_abs(x)/gsl_sf_log(2.0)) + 1023);
//    
//    //set the sign
//    s.SetAll((x >= 0.0 ? false : true));
//    
    
    
    uint8_t *bytePointer = (uint8_t *)&x;

    for(size_t index = 0; index < sizeof(double); index++)
    {
        uint8_t byte = bytePointer[index];

        for(int bit = 0; bit < 8; bit++)
        {
            printf("%d", byte&1);
            byte >>= 1;
        }
    }
    
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
        for(e_10=-1023.0, i=0; i<e.GetSize(); i++){
            e_10 += two_pow(i) * (e[i].Get(p));
        }
    
        cout << gsl_pow_int(-1.0, s.Get(p)) * gsl_pow_int(2.0, e_10) * b_10 << " ";
        
    }
    
    cout << "}\n";
        
}
