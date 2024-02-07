//
//  main.h
//  gillespie
//
//  Created by Michele on 07/02/2024.
//

#ifndef main_h
#define main_h


#endif /* main_h */

#define n_bits 64
const unsigned long long int ullong_1 = 1;

using namespace std;

class Bits{
  
private:
    unsigned long long int n;
    
public:
    
    Bits();
    Bits(unsigned long long int);
    
    void SetBit(unsigned int, bool);
    bool GetBit(unsigned int);
    void Print(void);
        
    
};



class Int{
    
private:
    
    //b[i] is the i-th bit of the representation of *this in base 2
    vector<unsigned long long int> b;
    
public:
    
    Int(void);
    Int(unsigned long long int);
    
    
//    void SetRandom(unsigned long long int);
    //bitwise sum
    Int operator + (const Int&);
    
};

class System{
    
public:
    
    unsigned long long int seed, /*the maximum number of molecules allowed for each species*/N;
    //the vector containing the numbers of molecules: x[i] is a vector. { x[i][0], x[i][1], x[i][2], ... } is the expression in base 2 of the number of molecules of species i
    vector<Int> x;
    gsl_rng* ran;
    
    System(void);
    System(unsigned int, unsigned int);
    void iterate(void);
    

};