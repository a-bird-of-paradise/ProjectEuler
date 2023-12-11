#include <iostream>
#include "Sieve.hpp"    
#include <algorithm>
#include <numeric>
#include <set>
#include <cmath> 
/*
n = qd + r
must have r<d
can take q>d WLOG
so small->large is r,d,q

(could have q,r,d but causes n^2 = m(m+1) which is not solvable in integers)

geometric: so r,d,q = r, ar, a^2r

common ratio of a, must be in Q, write a = b/c where both in N and gcd(b,c)=1

a = d/r = q/d = b/c
a^2 = q/r = b^2/c^2

must have c^2 | r for integer n, so, r = fc^2

r = fcc
d = ar = bfcc/c = fbc
q = a^2r = bb fcc / cc = fbb

n = qd + r
n = fbb.fbc + fcc
  = f^2 b^3 c + f c^2
  = fc(fb^3 + c)

  must have b > c.... 
  must have cbbb + cc < LIMIT

  c^3 < b^3 < fb^3 + c < n 
  so c < b < n^1/3 = 1e4

  similary, f^2 b^3 c < n
  -> f^2 < n / bbbc
  -> f < \sqrt(10^12/bbbc) = 10^6 / b \sqrt bc

*/

#define INT int64_t
#define LIMIT 1'000'000'000'000LL

int main(int argc, char **argv)
{
    INT answer = 0, q,d,r,n, n_root;

    std::set<INT> answers;

    for(INT b = 2; b <= std::powl(LIMIT,1.0/3.0); b++) {
        for(INT c = 1; c < b; c++) {

            if( c*std::powl(b,3.0)+ c*c > LIMIT) break;

            for(INT f = 1; f <= std::sqrtl(LIMIT / (std::powl(b,3.0)*c)); f++){
                r = f*c*c;
                d = f*b*c;
                q = f*b*b;
                n = q*d + r;

                if(n > LIMIT) break;
                n_root = std::sqrtl(n);

                if(n_root * n_root == n) answers.insert(n);
            }

        }
    }

    for(const auto& i : answers) std::cout << i << ' ' << std::sqrtl(i) << '\n';

    std::cout << std::accumulate(std::begin(answers),std::end(answers),0LL) << '\n';

    return 0;
}