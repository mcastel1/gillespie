
//a real number 0 <= 0 < 1  represented in base 2 in b: x = sum_{i=0}^{b.size()-1} 2^{i-b.size()} b[i]
class Fraction : public BitSet{
    
private:
    
    
public:
    
    Fraction(void);
    Fraction(unsigned int);
    void FloorMultiply(UnsignedInt*, UnsignedInt*);
    void GetBase10(vector<double>*);
    void PrintBase10(string);
    
//    friend class ;
    
};

