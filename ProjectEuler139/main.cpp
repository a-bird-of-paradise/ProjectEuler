#include <iostream>
#include "Sieve.hpp"    
#include <algorithm>
#include <cmath> 

/*

want: a^2 + b^2 = c^2
such that |a-b| | c

consider primitive triple 
from old textbook: |a-b| | c means |a-b| = 1
can generate via: 
a = m^2 - n^2 
b = 2mn
c = m^2 + n^2
for coprime n,m 
then:
a-b | c
m^2 - n^2 - 2mn = \pm 1 
(m-n)^2 - 2n^2 = \pm 1 
pell's equation! 
x^2 - 2y^2 = 1 
so solutions are convergents of \sqrt 2 
x = 1
y = 1
xn+1 = ⁢xn + 2 ⁢yn
yn+1 = xn + ⁢yn

generate (x,y) from convergents of \sqrt 2 
y = n, m-n = x -> m = x + y
a,b,c primitive triple 
but k solutions (a+b+c)k <= 100'000'000

*/

int main(int argc, char **argv)
{

    int64_t x_n,y_n, x_n1,y_n1, m,n, a,b,c, n_triangles = 0, perimiter = 0;
    const int64_t limit = 100'000'000;

    x_n = 1;
    y_n = 1;

    while(true)
    {

        n = y_n;
        m = x_n + y_n;

        a = m*m - n*n;
        b = 2*m*n;
        c = m*m + n*n;

        perimiter = a + b + c;

        if(perimiter >= limit) break;

        n_triangles += limit / perimiter;

        std::cout << x_n << ' ' << y_n << ' ' << a << ' ' << b << ' ' << c << '\n';

        x_n1 = x_n + 2*y_n;
        y_n1 = x_n + y_n;

        x_n = x_n1;
        y_n = y_n1;
    }

    std::cout << n_triangles << '\n';

    return 0;
}