#include <iostream>
#include "Sieve.hpp"    
#include <numeric>
/*

R(10^n) = (10^10^9-1) / 9 
divisible by prime p implies 
10^10^n = 1 mod 9p 

so just brute force through primes to see if 10 ^ (10^9) = 1 mod 9p

*/

int main(int argc, char **argv)
{
    std::vector<uint64_t> primes = GeneratePrimes(1'000'000ULL);

    uint64_t answer = 0, answer_count = 0;

    for(const auto& i : primes)
    {
        uint64_t cong = modular_power(10, 1'000'000'000, 9*i);

        if(cong == 1) {
            answer += i;
            answer_count++;
        }
        if(answer_count == 40) break;
    }

    if(answer_count != 40) abort();
    std::cout << answer << '\n';

    return 0;
}
