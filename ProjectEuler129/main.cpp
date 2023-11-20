#include <iostream>
#include "Sieve.hpp"

/*
Hmm this one is interesting. We want least n such that n | R(k) where k >= 1e6. 
Restriction is gcd(n,10) = 1.

Can limit search space via my old number theory textbook. Show n | R(k) primitively -> n >= k.

Suppose otherwise, then there exist 0 < i,j < k such that
R(k) = 10^i R(j) + R(i). 
This is congruent to 0 mod n.
And gcd(n,10) = 1. 
And k is the least k such that R(k) congruent to 0 mod n. 
And can choose i,j such that R(j) cong to R(i) mod n
(as n < k so there must be at least one collision).
But the partition can only be congruent to 0 mod n if one of R(i) and R(j) is. 
This violates the assumption. So n >= k. 

Path now clear. For each n >= 1e6, try all k<n to see if n | R(k). 
Can work modulo n at all times. 

Keep track of the prior r(k) mod n 
*/

int main(int argc, char **argv)
{

    long long least_k_seen = 0;
    long long n = 1'000'000;

    while(least_k_seen < 1'000'000)
    {
        if(n % 2 == 0 || n % 5 == 0) {
            n++;
            continue;
        }

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

        least_k_seen = k > least_k_seen ? k : least_k_seen;

        std::cout << "A(" << n << ") = " << k << '\n';

        n++;

    }

    return 0;
}
