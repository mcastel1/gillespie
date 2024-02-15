//
//  double.cpp
//  gillespie
//
//  Created by Michele on 10/02/2024.
//

#include "double.hpp"

//default constructor
inline Double::Double(void){
    
    b.Resize(52);
    e.Resize(11);
    
}

//set the fraction to zero, the exponent to 1023 and the sign to +
inline void Double::Clear(){
    
    unsigned int p;
    
    //set the fraction to zero
    for(p=0; p<b.GetSize(); p++){
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


//replace bit-by-bit *this with *replacer if *check=true, and leave *this unchanged otherwise
inline void Double::Replace(Double* replacer, Bits* check){
    
    unsigned int p;
    
    //replace the mantisssa
    for(p=0; p<(b.GetSize()); p++){
        b[p].Replace((replacer->b.b.data()) + p, check);
    }

    //replace the exponent
    for(p=0; p<(e.GetSize()); p++){
        e[p].Replace((replacer->e.b.data()) + p, check);
    }
    
    //replace the sign
    s.Replace(&(replacer->s), check);

}


//initialize *this randomly with seed seed
inline void Double::SetRandom(unsigned int seed){
    
    gsl_rng* ran;
    
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    gsl_rng_set(ran, seed);
    
    SetRandom(ran);
    
    gsl_rng_free(ran);

}


//initialize *this randomly with the (already initialized) random generator *ran
inline void Double::SetRandom(gsl_rng* ran){
    
    unsigned int i;
    
    for(i=0; i<b.GetSize(); i++){
        b[i].SetRandom(ran);
    }
    for(i=0; i<e.GetSize(); i++){
        e[i].SetRandom(ran);
    }
    s.SetRandom(ran);
    
}


void Double::Print(void){
    
    unsigned int i;
    
    cout << "\n";
    for(i=0; i<b.GetSize(); i++){
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



//set all entries of *this according to the double x, where x is written in binary according to the IEEE754 convention
inline void Double::SetAllVertically_IEEE754(double x){
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
    size_t index;
    uint8_t byte;
    int bit;
    unsigned int p;
    
    for(index=0, p=0; index < sizeof(double); index++){
        
         byte = bytePointer[index];

        for(bit = 0; bit < 8; bit++, p++){
            
//            printf("%d", byte & 1);
            
            if(p < b.GetSize()){
                
                b[p].SetAll(((bool)(byte & 1)));
                
            }else{
                
                if(p < b.GetSize()+e.GetSize()){
                    
//                    int temp;
//                    bool bb;
                    
//                    temp = p-(b.size());
//                    bb = ((bool)(byte & 1));
                    
//                    cout << "\nbefore";
//                    e[temp].Print();
                    
                    e[p-(b.GetSize())].SetAll(((bool)(byte & 1)));
//                    e[temp].SetAll(true);
//                    cout << "\nafter";
//                    e[temp].Print();

                }else{
                    
                    s.SetAll(((bool)(byte & 1)));

                    
                }
                
                
            }
            
            byte >>= 1;
        }
    }
    
}



//print *this in base 10 according to the IEEE754 convention
void Double::PrintBase10_IEEE754(void){
    
    unsigned int i, p;
    double b_10, e_10/*, A*/;
    
    cout << "Double in base 10: {";
    for(p=0; p<n_bits; p++){
        
        for(b_10=1.0, i=0; i<b.GetSize(); i++){
            b_10 += gsl_pow_int(2.0, -(i+1)) * (b[b.GetSize()-1-i].Get(p));
        }
        for(e_10=-1023.0, i=0; i<e.GetSize(); i++){
            e_10 += two_pow(i) * (e[i].Get(p));
        }
    
        cout << gsl_pow_int(-1.0, s.Get(p)) * gsl_pow_int(2.0, e_10) * b_10 << " ";
        
    }
    
    cout << "}\n";
        
}


//print *this in base 10 according to the my convention, where the mantissa is \sum_{i=0}^{52-1} b_{52-1-i} 2^{-i}
void Double::PrintBase10(void){
    
    unsigned int i, p;
    double b_10, e_10;
    
    cout << "Double in base 10: {";
    for(p=0; p<n_bits; p++){
        
        for(b_10=0.0, i=0; i<b.GetSize(); i++){
            b_10 += gsl_pow_int(2.0, -i) * (b[b.GetSize()-1-i].Get(p));
        }
        for(e_10=-1023.0, i=0; i<e.GetSize(); i++){
            e_10 += two_pow(i) * (e[i].Get(p));
        }
    
        cout << gsl_pow_int(-1.0, s.Get(p)) * gsl_pow_int(2.0, e_10) * b_10 << " ";
        
    }
    
    cout << "}\n";
        
}

//sum *this to addend and write the result in *this
inline void Double::operator += (Double& x){
    
    Double augend, addend;
    Bits compare;
    
    
    //set (augend.e) and (addend.e), compare the two bit-by-bit and write the result in compare
    (augend.e) = e;
    (addend.e) = (x.e);
    compare = ((augend.e) < (addend.e));
    
    //swap bit-by-bit (augend.e) and (addend.e) in such a way that (augend.e) >= (addend.e)
    augend.Replace(&x, &compare);
    addend.Replace(this, &compare);
    
  

}
