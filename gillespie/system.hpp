//
//  system.hpp
//  gillespie
//
//  Created by Michele on 07/02/2024.
//

#ifndef system_hpp
#define system_hpp

#include <stdio.h>

#endif /* system_hpp */

//a reaction-diffusion system
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
