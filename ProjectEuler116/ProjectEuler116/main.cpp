#include <iostream>
#include <gmpxx.h>
#include <map>

std::map<int,mpz_class> FactorialCache;
int FactorialCache_max = -1;

std::map<std::pair<int,int>,mpz_class> BinomialCache;

mpz_class Factorial(int x)
{
    mpz_class Answer = 1;
    
    std::map<int,mpz_class>::const_iterator it;
    
    it = FactorialCache.find(x);
    
    if(it == FactorialCache.end())
    {
        mpz_class i = 1;
        if(FactorialCache_max >= 0 && x > FactorialCache_max)
        {
            Answer = FactorialCache[FactorialCache_max];
            i = FactorialCache_max+1;
        }
        while(i <= x)
        {
            Answer *= i;
            i++;
        }
        FactorialCache[x] = Answer;
        FactorialCache_max = x;
    }
    else{
        Answer = it->second;
    }
    return Answer;
}

mpz_class BinomialValue(const int& n, const int& k)
{
    
    mpz_class Answer;
    
    std::pair<int,int> ThePair;
    ThePair.first = n;
    ThePair.second = k;
    
    std::map<std::pair<int,int>,mpz_class>::const_iterator it;
    
    it = BinomialCache.find(ThePair);
    
    if(it==BinomialCache.end())
    {
        Answer = Factorial(n) / ( Factorial(k) * Factorial(n-k));
        BinomialCache[ThePair]=Answer;
        ThePair.second = n-k;
        BinomialCache[ThePair]=Answer;
    }
    else
    {
        Answer = it -> second;
    }
    
    return Answer;
}

mpz_class g(const int n, const int x)
{
    int rmax = n / x;
    mpz_class Answer = 0;
    
    for(int r = 1; r <= rmax; r++)
    {
        Answer += BinomialValue(n-(x-1)*r, r);
    }
    return Answer;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    const int n = 50;
    //std::cout << g(n,2) << "|" << g(n,3) << "|" << g(n,4) << std::endl;
    
    std::cout << g(n,2)+g(n,3)+g(n,4) << std::endl;
    
    return 0;
}
