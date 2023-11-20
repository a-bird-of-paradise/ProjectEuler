#include <iostream>
#include "Sieve.hpp"
#include <algorithm>
#include <numeric>

long long A(long long n)
{
    if(n % 2 == 0 || n % 5 == 0) return 0;

    // initialise: 

    long long k = 1;
    long long position = 1; // this holds the next digit mod n 
    // basically a number like 10000...0000, as I need to track its mod to produce
    long long r = 1;  // holds R(k) mod n 

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

    std::vector<long long> primes = GeneratePrimes<long long>(20'000);

    std::vector<long long> answers;
    answers.reserve(25);

    long long n = 10;

    while(answers.size() < 25)
    {
        if(n % 2 == 0 || n % 5 == 0 || std::binary_search(primes.begin(),primes.end(),n) == true) {
            n++;
            continue;
        }

        long long A_n = A(n);
        long long remainder = (n-1) % A_n;

        if(remainder == 0) answers.push_back(n);

        n++;

    }

    std::cout << std::accumulate(answers.begin(),answers.end(),0) << std::endl;

    return 0;
}
