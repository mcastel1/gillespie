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
    vector<UnsignedInt> /*the vector containing the numbers of molecules: x[i] is a vector. { x[i].b[0], x[i].b[1], x[i].b[2], ... } is the expression in base 2 of the number of molecules of species i, x[0] -> L, x[1] -> D, x[2] -> A*/x, /*the reaction rates: a[j](x) = c[j] * f(x), where c[j] is independent of x*/c, /*the quantities a_j in Gillespie algorithm, a[0] corresponds to the resction A+D -> 2D, a[1] to the reaction A+L -> 2L, a[2] to the reaction D+L->2A*/a;
    //the random number used to draw the reaction, equal to r2 in Eq. (10b) in gillespie2007stochastic
    Fraction R;
    gsl_rng* ran;
    
    System(void);
    System(unsigned long long int, unsigned int);
    void Iterate(void);
    

};
