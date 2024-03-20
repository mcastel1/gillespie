//
//  system_nobits.hpp
//  gillespie
//
//  Created by Michele on 07/02/2024.
//

//a reaction-diffusion System with bits framework
class SystemBits{
    
public:
    
    unsigned long long int seed, /*the total number of molecules in the system*/N;
    vector<UnsignedInt> /*the vector containing the numbers of molecules: x[i] is a vector. { x[i].b[0], x[i].b[1], x[i].b[2], ... } is the expression in base 2 of the number of molecules of species i, x[0] -> A, x[1] -> L, x[2] -> D*/x, /*the reaction rates: a[j](x) = c[j] * f(x), where c[j] = 1 for simplicity */ /*the quantities a_j in Gillespie algorithm, a[0] corresponds to the resction A+L -> 2L, a[1] to the reaction A+D -> 2D, a[2] to the reaction L+D->2A*/a;
    vector<bool> /*a temporary variable used to store the bits of the mantissa of the random number r_2*/ w;
    UnsignedInt /*the left-hand side of Eq. (10b) in gillespie2007stochastic*/L, /*the random number used to draw the reaction, which represents r2 in Eq. (10b) in gillespie2007stochastic*/ R;
    //changer[j] sets which out of the n_bits replicas has undergone reaction j: if the s-th bit of changer[j] = 0 then the s-th replica has not undergone the reaction j, while if it = 1, the s-th replica has undergone the reaction j
    Bits compare_old, compare_new, changer;
    //the random number used to draw the reaction time, equal to r1 in Eq. (10a) in gillespie2007stochastic
    double r1;

   
    unsigned long int q;
    //a temporary variable to store the carry of operations
    Bits carry, borrow;
    gsl_rng* ran;
    
    SystemBits(void);
    SystemBits(unsigned long long int, unsigned int);
    void Iterate(void);
    

};


//a reaction-diffusion system without bits framework
class systemnobits{
    
public:
    
    unsigned long long int seed, /*the total number of molecules in the system*/N, /*the left-hand side of Eq. (10b) in gillespie2007stochastic*/L, /*the random number used to draw the reaction, which represents r2 in Eq. (10b) in gillespie2007stochastic*/  R;
    vector<unsigned int> /*the vector containing the numbers of molecules:  x[0] -> A, x[1] -> L, x[2] -> D*/x, /*the reaction rates: a[j](x) = c[j] * f(x), where c[j] is independent of x*//*c,*/ /*the quantities a_j in Gillespie algorithm, a[0] corresponds to the resction A+L -> 2L, a[1] to the reaction A+D -> 2D, a[2] to the reaction L+D->2A*/a;
    unsigned int  /*this is a_0 in gillespie2007stochastic*/z, rhs;
    //the random number used to draw the reaction time, equal to r1 in Eq. (10a) in gillespie2007stochastic
    double r1;
    //a temporary variable to store the carry of operations
    gsl_rng* ran;
    
    systemnobits(void);
    systemnobits(unsigned long long int, unsigned int);
    void iterate(void);

};
