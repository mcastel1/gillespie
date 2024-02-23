//
//  double.hpp
//  gillespie
//
//  Created by Michele on 10/02/2024.
//

//a (collection of n_bits) double(s) represented in base 2
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
    void Normalize(void);
    void Replace(Double*, Bits*);
    void Swap(Double*, Bits&, Bits*);
    void SetAll_IEEE754(double);
    void SetAll(bool, unsigned long long int, double);
    void Set(unsigned int, bool, unsigned long long int, double);
    void SetAll(bool, unsigned long long int, BitSet&);
    void SetRandom(gsl_rng*);
    void SetRandom(unsigned int);
    void Print(void);
    void PrintBase10_IEEE754(void);
    void PrintBase10(string);
    void GetBase10(vector<double>&);

    void Add(Double*, Double*);
    void operator += (Double*), operator *= (Double&);
    Bits operator <(Double&);

};
