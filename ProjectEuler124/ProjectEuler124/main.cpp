#include <iostream>
#include <utility>
#include "Sieve.h"

std::vector<uint32_t> Primes = GeneratePrimes<uint32_t>(100000);

uint32_t Radical(uint32_t n)
{
    uint32_t answer = 1;
    
    for(std::vector<uint32_t>::const_iterator i = Primes.begin();
        i != Primes.end();
        ++i)
    {
        if(*i > n) break;
        if(n % *i == 0) answer *= *i;
    }
    
    return answer;
}

bool pairCompare(const std::pair<uint32_t, uint32_t>& firstElem,
                 const std::pair<uint32_t, uint32_t>& secondElem)
{
    bool answer;
    
    if(firstElem.second == secondElem.second)
    {
        answer = firstElem.first < secondElem.first;
    }
    else
    {
        answer = firstElem.second < secondElem.second;
    }
    return answer;
}

int main(int argc, const char * argv[])
{
    std::vector<std::pair<uint32_t,uint32_t>> Elements;
    
    for(uint32_t i = 1; i <= 100000; ++i)
    {
        Elements.push_back(std::make_pair(i, Radical(i)));
    }

    std::sort(Elements.begin(), Elements.end(), pairCompare);
    
    std::cout << Elements[10000-1].first << std::endl;
    
    return 0;
    
}
