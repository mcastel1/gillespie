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
    vector<UnsignedInt> /*the vector containing the numbers of molecules: x[i] is a vector. { x[i].b[0], x[i].b[1], x[i].b[2], ... } is the expression in base 2 of the number of molecules of species i*/x, /*the reaction rates: a[j](x) = c[j] * f(x), where c[j] is independent of x*/c, /*the quantities a_j in Gillespie algorithm*/a;
    gsl_rng* ran;
    
    System(void);
    System(unsigned long long int, unsigned int);
    void Iterate(void);
    

};
