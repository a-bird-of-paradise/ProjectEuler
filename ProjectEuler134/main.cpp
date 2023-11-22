#include <iostream>
#include "Sieve.hpp"    
#include <algorithm>

/*
Chinese remainder theorem
*/

template <typename T>
T mod_digits(const T p) 
{
    T answer = 10;
    while(p >= answer) answer *= 10;
    return answer;
}

template <typename T>
T minsum(T p_1, T p_2)
{
    T digits = mod_digits(p_1);
    bezout<T> out = gcd_extended(digits,p_2);

    T answer = ((p_1 * out.y * p_2) % (p_2 * digits));
    if(answer < 0) answer += (p_2 * digits);
    return answer;
}

int main(int argc, char **argv)
{
    std::vector<int64_t> primes = GeneratePrimes<int64_t>(1'000'100);

    std::vector<int64_t>::iterator p_1, p_2;

    p_1 = primes.begin();
    while(*p_1 != 5) p_1++;
    p_2 = std::next(p_1);

    int64_t answer = 0;

    while(*p_1 <= 1'000'000)
    {
        answer += minsum(*p_1, *p_2);

        p_1 = std::next(p_1);
        p_2 = std::next(p_2);
    }

    std::cout << answer << std::endl;

    return 0;
}

// 163234212717118 is wrong