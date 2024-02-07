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


class Int;
class Bits;


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
