#include <iostream>
#include <gmpxx.h>

mpz_class Factorial(const mpz_class& x)
{
    mpz_class Answer = 1;
    
    mpz_class i = 1;
    
    while(i <= x)
    {
        Answer *= i;
        i++;
    }
    return Answer;
}

mpz_class BinomialValue(const mpz_class& n, const mpz_class& k)
{
    return Factorial(n) / ( Factorial(k) * Factorial(n-k));
}

mpz_class F(mpz_class n, mpz_class m)
{
    mpz_class rmax = (n+1) / (m+1);
    
    mpz_class Answer = 0, r;
    
    for(mpz_class i = 0; i <= rmax; i++)
    {
        r=i;
        Answer += BinomialValue(n - (m-1)*r -1, (2*r - 2));
        Answer += 2*BinomialValue(n - (m-1)*r -1, (2*r - 1));
        Answer += BinomialValue(n - (m-1)*r -1, (2*r - 0));
    }
    
    return Answer;
    
}

int main(int argc, const char * argv[]) {
    
    int m = 50, n = m + 10;
    mpz_class Answer;
    do  {
        n++;
        Answer = F(n, m);
    } while(Answer < 1000000);
    
    std::cout << n << std::endl;
    
    return 0;
}
