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
#include "gsl_sf_pow_int.h"
#include "main.h"


inline unsigned long long int two_pow(unsigned long long int i){
    
    return ((unsigned long long int)gsl_sf_pow_int(2.0, ((int)i)));
    
}

//return the number of bits necessary to write n in base 2
unsigned int inline bits(unsigned long long int n){
    
    unsigned int s;
    
    for(s=0; two_pow(s) <= (unsigned long long int)n; s++){}
    
    return s;
    
}


Bits::Bits(){}

Bits::Bits(unsigned long long int n_in){
    
    n  = n_in;
    
}


//set the i-th entry of input equal to bit
void Bits::SetBit(unsigned int s, bool bit){
    
    unsigned int p;
    unsigned long long int result;
    
    result = 0;
    for(p=0; p<n_bits; p++){
        
        if(p!=s){
            
            result |= (((n >> p) & ullong_1) << p);
            
        }else{
            
            if(bit){
                result |= (ullong_1 << s);
            }
            
        }
        
    }
    
    n = result;
    
}

//return the s-th bit ofinput
bool Bits::GetBit(unsigned int s){
    
    return ((n >> s) & ullong_1);
    
}


void Bits::Print(void){
    
    cout << "Bits = {";
    for(unsigned int s=0; s<n_bits; s++){
        cout << this->GetBit(n_bits-1-s);
    }
    cout << " }";
    
}

Int::Int(void){
        
}

Int::Int(unsigned long long int N){
    
    b.resize(bits(N));
    
}


inline Int Int::operator+ (const Int& addend) {
    
    Int result(b.size()), carry(b.size());
    unsigned int p, s;
    
    
    p=0;
    
    for(s=0; s<b.size(); s++){
        
        if(s==0){
            carry.b[s] = ((b[s]) & (addend.b[p]));
            (b[s])^= (addend.b[p]);
        }else{
            carry.b[s] = ((b[s]) & (carry.b[s-1]));
            (b[s])^= (carry.b[s-1]);
        }
        
    }
    
    return result;

}



/*
void Int::SetRandom(unsigned long long int seed){
    
    int i;
    gsl_rng* ran;

    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    gsl_rng_set(ran, seed);

    
    for(i=0; i<b.size(); i++){
        
        
    }
    
}
 */



System::System(void){
    
}


System::System(unsigned int N_in, unsigned int seed_in){
    
    unsigned int i;
    
    ran = gsl_rng_alloc(gsl_rng_gfsr4);

    N = N_in;
    seed = seed_in;

    for(x.clear(), i=0; i<3; ++i){
        x.push_back(Int(N));
    }
    
    gsl_rng_set(ran, seed);
    
}

void System::iterate(void){
    
    
    
}



int main(int argc, char * argv[]) {
    
    int options;
    unsigned int seed=0, N=0, s;
    

    while ((options = getopt(argc, argv, ":N:s:")) != -1) {
         
         switch (options) {
                 
             case 'N':
                 N = ((unsigned int)atoi(optarg));
                 break;
                 
             case 's':
                 seed = ((unsigned int)atoi(optarg));
                 break;
                 
         }
         
     }
     
    System sys(N, seed);
    
    Bits a(4);
    a.Print();
    a.SetBit(12, true);
    a.Print();
    
    
    
    return 0;
    
}
