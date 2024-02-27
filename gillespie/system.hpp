//
//  system.hpp
//  gillespie
//
//  Created by Michele on 07/02/2024.
//

//a reaction-diffusion system
class System{
    
public:
    
    unsigned long long int seed, /*the total number of molecules in the system*/N;
    //the vector containing the numbers of molecules: x[i] is a vector. { x[i].b[0], x[i].b[1], x[i].b[2], ... } is the expression in base 2 of the number of molecules of species i
    vector<UnsignedInt> x;
    gsl_rng* ran;
    
    System(void);
    System(unsigned int, unsigned int);
    void Iterate(void);
    

};
