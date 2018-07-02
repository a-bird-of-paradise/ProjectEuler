#include <iostream>
#include "Sieve.h"
#include <limits>
#include <gmpxx.h>

typedef mpz_class INT;

INT ExpMod(INT base, INT exponent, INT modulus)
{
    INT answer;
    if(modulus == 1)
    {
        answer = 0;
    }
    else
    {
        answer = 1;
        base = base % modulus;
        while(exponent > 0)
        {
            if(exponent % 2 == 1)
            {
                answer = (answer * base) % modulus;
            }
            
            exponent /= 2;
            
            base = (base * base) % modulus;
        }
    }
    return answer;
}

INT f(INT n, INT p_n)
{
    INT x, y, answer;
    
    x = ExpMod(p_n - 1, n, p_n*p_n);
    y = ExpMod(p_n + 1, n, p_n*p_n);
    
    answer = (x + y) % (p_n*p_n);
    
    return answer;
}

int main(int argc, char** argv)
{
    std::vector<INT> Primes = GeneratePrimes<INT>(std::pow(10,6));
    
    INT MaxMod = std::numeric_limits<INT>::min();
    INT finish = 1;
    finish *= 10*10*10;
    finish *= 10*10*10;
    finish *= 10*10*10;
    finish *= 10;
    
    INT i = 0, temp;
    
    while(MaxMod < finish)
    {
        temp = f(i+1,Primes[i.get_ui()]);
        
        if(temp > MaxMod)
        {
            //std::cout << i+1 << "|" << temp << std::endl;
            MaxMod = temp;
        }
        
        i++;
    }
    
    std::cout << i << std::endl;
    
    return 0;
}