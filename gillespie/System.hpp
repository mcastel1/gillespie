//
//  system_nobits.hpp
//  gillespie
//
//  Created by Michele on 07/02/2024.
//

//a reaction-diffusion System with bits framework
class System_bits{
    
public:
    
    unsigned long long int seed, /*the total number of molecules in the system*/N;
    vector<UnsignedInt> /*the vector containing the numbers of molecules: x[i] is a vector. { x[i].b[0], x[i].b[1], x[i].b[2], ... } is the expression in base 2 of the number of molecules of species i, x[0] -> A, x[1] -> L, x[2] -> D*/x, /*the reaction rates: a[j](x) = c[j] * f(x), where c[j] is independent of x*/c, /*the quantities a_j in Gillespie algorithm, a[0] corresponds to the resction A+L -> 2L, a[1] to the reaction A+D -> 2D, a[2] to the reaction L+D->2A*/a;
    vector<bool> /*a temporary variable used to store the bits of the mantissa of the random number r_2*/ w;
    UnsignedInt /*a temporary variable used to store the product x[]*x[]*/A, /*worrk space */W, /*this is a_0 in gillespie2007stochastic*/Z, /*the right-hand side of Eq. (10b) in gillespie2007stochastic*/RHS;
    //the random number used to draw the reaction, equal to r2 in Eq. (10b) in gillespie2007stochastic
    Fraction R;
    //a temporary variable to store the carry of operations
    Bits carry;
    gsl_rng* ran;
    
    System_bits(void);
    System_bits(unsigned long long int, unsigned int);
    void Iterate(void);
    

};


//a reaction-diffusion system without bits framework
class System_nobits{
    
public:
    
    unsigned long long int seed, /*the total number of molecules in the system*/N;
    vector<unsigned int> /*the vector containing the numbers of molecules:  x[0] -> A, x[1] -> L, x[2] -> D*/x, /*the reaction rates: a[j](x) = c[j] * f(x), where c[j] is independent of x*/c, /*the quantities a_j in Gillespie algorithm, a[0] corresponds to the resction A+L -> 2L, a[1] to the reaction A+D -> 2D, a[2] to the reaction L+D->2A*/a;
    unsigned int  /*this is a_0 in gillespie2007stochastic*/Z;
    //the random number used to draw the reaction, equal to r2 in Eq. (10b) in gillespie2007stochastic
    double r;
    //a temporary variable to store the carry of operations
    gsl_rng* ran;
    
    System_nobits(void);
    System_nobits(unsigned long long int, unsigned int);
    void iterate(void);

};
