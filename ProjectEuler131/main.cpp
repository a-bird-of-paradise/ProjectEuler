#include <iostream>
#include "Sieve.hpp"    
#include <algorithm>
/*
n^3 + n^2p = m^3
so 1 + p/n = m^3 / n^3
i.e. cube root of 1+p/n is rational

write as (n+p)/n

then n+p = a^3 and n = b^3 

solve for p, get p = a^3 - b^3 
= (a-b)(a^2 + ab + b^2)
p prime so a = b+1
so  (b+1)^2 + (b+1)b + b^2
= b^2 + 2b + 1 + b^2 + b + b^2
= 3b^2 + 3b + 1
= 3b(b+1) + 1

or b = a-1
so a^2 + a(a-1) + (a-1)^2
= a^2 + a^2 - a + a^2 -2a +1
= 3a^2 -3a + 1
= 3a(a-1) + 1

ok. form candidates from a \in (2,1000) as p = 3a(a-1) + 1
test if p in primes

*/

int main(int argc, char **argv)
{

    std::vector<int32_t> primes = GeneratePrimes(1'000'000);

    uint32_t answer = 0;

    for(int64_t a = 2; a < 600; a++)
    {
        int64_t p = 3*a*(a-1) + 1;
        if(std::binary_search(std::begin(primes),std::end(primes),p)) answer++;
    }

    std::cout << answer << '\n';
    return 0;
}
