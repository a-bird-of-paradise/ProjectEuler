#include <iostream>
#include "cube.hpp"
#include "Sieve.hpp"
#include <map>
#include <algorithm>
#include <set>

/*
Well. My laborious cube building did not scale
(although https://www.redblobgames.com/grids/hexagons is an outstanding resource).

Did notice that the (q,r,s) output of answers always had s = 0 or 1, i.e. always first or last 
in a ring. Could I prove this? 

Reminder: we are after prime differences, and for x-y to be prime it must be 2 or odd
So if z = y+1, at most one of x-y and x-z can be prime (save some funnies around 2 and 3,
so assume x and y are far enough apart, i.e. third ring onwards)

Classify elements as:
generic edge
generic corner
special edge (last)
special corner (first)

Generic edge: this always has its follower and leader elements, i.e. two elements with a
    difference of 1. Not prime. And the 'inner' and 'outer' sections always have a sequence in it,
    so at most 1 of the two hexes in each section can admit a prime difference (as we're far enough
    out for the 2,3 thing not to matter). So edges can never have PD(3). 

Generic corner. Again this always has its leader and follower in it so we can knock those two out.
    It has one interior hex and three (sequential) exterior hexes. So we must have the 
    interior hex and the two extremal exterior hexes admitting prime differences. 
    Easy enough to see that the difference between the corner and its interior corner is
    6r + n
    where r is this ring and n is this corner (0 based, up 0, count anticlockwise)
    So the n = 2, 4 corners can never have an odd interior difference. 
    Exterior corners. Difference is 6(r+1) + n to the middle node, which must be even, for the
    extramal hexes to have odd differences.
    Which means, as n = 1,3,5, that 6(r+1) has to be odd, a contradiction. 
    So generic corners never have PD(3). 

Phew. 

This leaves the specials which just have to be inspected. The 'last' hex in each layer is
We can use https://en.wikipedia.org/wiki/Centered_hexagonal_number to make life easier.

So 'up": we have H(n)+1 for some n. The up and down directions are H(n+1)+1 and H(n-1)+1, which
are also even numbers, thus always an even difference, and never 2 once we are far out enough. 
We also have the follower noe H(n)+2 as a neighbour, never a prime difference. 

Consider the neighbours H(n+1)+2, H(n+2), H(n+1). 

And 'last', we have H(n). Have H(n+1) up and H(n-1) down, which always admit even differences, 
and big enough even differences to never be prime. And have the follower H(n)-1 which is 
always 1. 

So consider H(n+1)-1, H(n-1)+1, H(n-2)+1. 

*/

long long H(const long long n)
{
    return 3*n*n - 3*n + 1;
}

int main(int argc, char **argv)
{
    std::cout << "Generating primes\n";

    std::vector<long long> primes = GeneratePrimes<long long>(10000000), answers;
    long long n = 3;

    // add special cases generated with n <= 2

    answers.push_back(1);
    answers.push_back(2);
    answers.push_back(8);

    std::cout << "Finding solutions\n";

    while(answers.size() < 2002)
    {
        long long value = H(n);

        long long candidate_1 = H(n+1)-1, 
            candidate_2 = H(n-1)+1, 
            candidate_3 = H(n-2)+1;

        // diffs;
        candidate_1 = candidate_1 - value;
        candidate_2 = value - candidate_2;
        candidate_3 = value - candidate_3;

        if(std::binary_search(primes.begin(), primes.end(), candidate_1) 
            && std::binary_search(primes.begin(), primes.end(), candidate_2)
            && std::binary_search(primes.begin(), primes.end(), candidate_3))
        {
            answers.push_back(value);
        }

        value = H(n)+1;
        candidate_1 = H(n+1)+2;
        candidate_2 = H(n+2);
        candidate_3 = H(n+1);

        candidate_1 = candidate_1 - value;
        candidate_2 = candidate_2 - value;
        candidate_3 = candidate_3 - value;

        if(std::binary_search(primes.begin(), primes.end(), candidate_1) 
            && std::binary_search(primes.begin(), primes.end(), candidate_2)
            && std::binary_search(primes.begin(), primes.end(), candidate_3))
        {
            answers.push_back(value);
        }

        n++;
    }

    std::cout << answers[2000-1] << std::endl; // 0 based

    return 0;
}
