//
//  double.hpp
//  gillespie
//
//  Created by Michele on 10/02/2024.
//

//a double represented in base 2
class Double{
    
private:
    
    //the fraction: b has size 52
    BitSet b;
    //the exponent: e.b has size 11
    UnsignedInt e;
    //the sign
    Bits s;
    
public:
    
    Double(void);
    void Clear(void);
    void Replace(Double*, Bits*);
    void SetAll_IEEE754(double);
    void SetAll(bool, unsigned long long int, BitSet&);
    void SetRandom(gsl_rng*);
    void SetRandom(unsigned int);
    void Print(void);
    void PrintBase10_IEEE754(void);
    void PrintBase10(void);
    void GetBase10(vector<double>&);

    void operator += (Double&);

};
