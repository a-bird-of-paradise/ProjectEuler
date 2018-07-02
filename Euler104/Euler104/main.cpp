#include <iostream>
#include <gmpxx.h>
#include <ctime>

bool is_pandigital(const mpz_class& ToTest, const int base=10)
{
    bool* SeenIndex = new bool[base];
    
    //bool SeenIndex[10];
    
    for(int i = 0; i < base; i++)
        SeenIndex[i]=false;

    mpz_class Quotient, Remainder, x, zBase;
    
    zBase = base;
    
    x = ToTest;
    
    while(x > 0)
    {
        Quotient = x / zBase;
        Remainder = x % zBase;
        x = Quotient;
        SeenIndex[Remainder.get_si()] = true;
    }
    
    bool Answer = true;
    for(int i = 1; i < base; i++) // don't care about zeroes
        Answer = Answer && SeenIndex[i];
    
    delete[] SeenIndex;
    return Answer;
}

mpz_class Reverse(const mpz_class& Orig, const int base = 10)
{
    mpz_class Answer = 0, x = Orig;
    
    while ( x > 0 )
    {
        Answer *= base;
        Answer += x % base;
        x /= base;
    }
    return Answer;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    std::clock_t start, end;
    start = clock();
    
    mpz_class x, y, z;
    
    x = 1;
    y = 1;
    
    const mpz_class tendigits = 1000000000;
    
    for(int i = 3; i <= 1000000; i++)
    {
        z = x + y;
        if(is_pandigital(z % tendigits) && is_pandigital(Reverse(z) % tendigits))
        {
            std::cout << i << std:: endl;
            break;
        }
        x = y;
        y = z;
    }
    
    end = clock();
    
    std::cout << "Elapsed: " <<
        static_cast<double>((end-start)/CLOCKS_PER_SEC) << std::endl;
    return 0;
}
