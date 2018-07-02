#pragma once
#include <vector>
#include <cmath>

// generate primes

template<typename T>
std::vector<T> GeneratePrimes(uint64_t UpTo)
{
    std::vector<T> Answers;
    std::vector<char> Numbers;
    Numbers.resize(UpTo + 1);
    for(std::size_t i = 0; i <= UpTo; i++)
        Numbers[i] = true;
    
    T loopmax = std::sqrt(UpTo);
    
    for(std::size_t i = 2; i <= loopmax; i++)
    {
        if(Numbers[i] == false) continue;
        std::size_t j = 2;
        while(i*j <= UpTo)
        {
            Numbers[i*j] = false;
            j++;
        }
    }
    for(std::size_t i = 2; i <= UpTo; i++)
        if(Numbers[i])
            Answers.push_back(i);
    
    return Answers;
    
}

