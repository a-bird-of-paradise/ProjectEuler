#include <iostream>
#include "Sieve.hpp"    
#include <algorithm>
#include <cmath>
#include <set>
/*
law of cosines:
a^2 = p^2 + r^2 -2pr cosA
but know A = 120deg 
so a^2 = p^2 + r^2 + pr
sim b^2 = q^2 + p^2 + pq
c^2 = r^2 + q^2 + qr

so:
try all p+q+r, see if a,b,c squares

*/

#define INT int64_t
#define LIMIT 120'000LL

bool is_square(INT x)
{
    INT s = sqrt(x);
    return ((s * s) == x) ;
}

int main(int argc, char **argv)
{

    std :: cout << "Generating squares...\n";

    std::vector<INT> squares(3*LIMIT+1);
    for(INT i = 0; i < 3*LIMIT+1; ++i) squares[i] = i*i;

    INT answer = 0;
    std::set<INT> answers;

    std :: cout << "Seeking squares...\n";

    for(INT p = 1; p < LIMIT; ++p) {
        for(INT q = 1; q <= p; ++q) {
            if(p+q > LIMIT) break;
            for(INT r = 1; r <= q; ++r) {
                if(p+q+r > LIMIT) break;
                INT asq = p*p + r*r + p*r;
                INT bsq = p*p + q*q + p*q;
                INT csq = q*q + r*r + q*r;
                if(!is_square(asq) || !is_square(bsq) || !is_square(csq)) continue;
                std::cout << "p: " << p << ", q: " << q << ", r: " << r << 
                            ", a: " << std::sqrt(asq) << 
                            ", b: " << std::sqrt(bsq) << 
                            ", c: " << std::sqrt(csq) <<
                            ", p+q+r: " << p+q+r
                            << '\n';
                answers.insert(p+q+r);
            }
        }
    }

    for(const auto & pqr : answers)
    {
        answer += pqr;
    }

    std::cout << answer << '\n';
    // not 32029046
    return 0;
}