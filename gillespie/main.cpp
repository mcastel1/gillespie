//
//  main.cpp
//  gillespie
//
//  Created by Michele on 25/01/2024.
//

#include <iostream>

#include "gsl_rng.h"

using namespace std;

class System{
    
public:
    
    long n_species, n_reactions;
    vector<long> x;
    
    System(long, long);
    

};

System::System(long n_species_in, long n_reactions_in){
    
    n_species = n_species_in;
    n_reactions = n_reactions_in;
    x.resize(n_species);
    
}



int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
    
}
