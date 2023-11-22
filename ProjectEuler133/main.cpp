#include <iostream>
#include "Sieve.hpp"    
#include <numeric>
/*

previously: have A(n) = least k such that R(k) = 0 mod n

prime p never divides R(10^n) implies gcd(p,A(n)) = 1

i.e. A(n) only has 2s and 5s in its factors

*/

uint32_t A(uint32_t n)
{
    if(n % 2 == 0 || n % 5 == 0) return 0;

    // initialise: 

    uint32_t k = 1;
    uint32_t position = 1; // this holds the next digit mod n 
    // basically a number like 10000...0000, as I need to track its mod to produce
    uint32_t r = 1;  // holds R(k) mod n 

    while(r % n != 0) 
    {
        k++;

        position *= 10; // add the next 1, at the left
        position %= n; // mod n of course

        r += position; // construct the next R(k)
        r %= n; // mod n duh 
    }
    return k;
}


int main(int argc, char **argv)
{
    std::vector<uint32_t> primes = GeneratePrimes(static_cast<uint32_t>(100'000));

    uint64_t answer = 0;

    for(const auto& i : primes)
    {
        if(i == 2 || i == 5) { answer += i; continue; }
        uint32_t a = A(i);
        while(a % 2 == 0) a /= 2;
        while(a % 5 == 0) a /= 5; 
        if(a != 1) answer += i;

    }
    std::cout << answer << '\n';

    return 0;
}
