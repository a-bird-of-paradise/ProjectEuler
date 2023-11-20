#pragma once
#include <vector>
#include <cmath>

// generate primes

template<typename T>
std::vector<T> GeneratePrimes(T UpTo)
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
            Answers.push_back(static_cast<T>(i));
    
    return Answers;
    
}

template<typename T>
std::vector<T> GenerateRadicals(T UpTo)
{
    std::vector<T> Radicals;
    Radicals.resize(UpTo + 1);
    for(std::size_t i = 0; i <= UpTo; i++)
        Radicals[i] = 1;
    
    for(std::size_t i = 2; i <= UpTo; i++)
    {
        if(Radicals[i] != 1) continue; // not prime
        std::size_t j = 1;
        while(i*j <= UpTo)
        {
            Radicals[i*j] *= i;
            j++;
        }
    }
    return Radicals;
    
}

template<typename T>
std::vector<T> GenerateSquareFreeNumbers(const T UpTo)
{
    std::vector<T> Answers;
    std::vector<char> IsSquareFree;
    IsSquareFree.resize(UpTo + 1);
    for(auto&& i : IsSquareFree) i = true;
    
    T loopmax = std::sqrt(UpTo);
    T ThisNum;
    
    for(std::size_t i = 2; i <= loopmax; i++)
    {
        if(IsSquareFree[i] == false) continue; // skip over already known squares
        std::size_t j = 2;
        ThisNum = i * j;
        while( ThisNum <= UpTo)
        {
            if(ThisNum % (i*i) == 0 ) IsSquareFree[ThisNum] = false;
            j++;
            ThisNum = i * j;
        }
    }
    for(std::size_t i = 1; i <= UpTo; i++)
        if(IsSquareFree[i])
            Answers.push_back(static_cast<T>(i));
    
    return Answers;
}

template<typename T>
T Radical(T n, const std::vector<T>& Primes)
{
    T answer = 1;
    
    if(n > 1)
    {
        for(typename std::vector<T>::const_iterator i = Primes.begin();
            i != Primes.end();
            ++i)
        {
            if(*i > n) break;
            if(n % *i == 0) answer *= *i;
        }
    }
    return answer;
}

template<class T>
inline T gcd(T a, T b) {
    while(b) {
        auto t = a % b;
        a = b;
        b = t;
    }
    return a;
}

template<class T>
inline bool are_comprimes(T a, T b) {
    if(!((a | b) & 1))
        return false; // Both are even numbers, divisible by at least 2.
    return 1 == gcd(a, b);
}
