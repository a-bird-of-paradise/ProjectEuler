#include <iostream>
#include "Sieve.hpp"    
#include <algorithm>
#include <cmath> 
#include <set>
/*

Isosceles triangles - height h, breadth b, 2x L lengths

height = sqrt(L^2 - b^/4)
h^2 = L^2 - b^2/4

but h = b\pm1
h \pm 1 = b
(h\pm 1)^2 / 4...

so b^2 \pm 2b + 1 - L^2 -b^2/4
5b^2/4 \pm 2b + 1 = L^2 
4|b^2 => b even

just brute force it, see if it works
... no, precision issues
use a = b/2 so h = 2a \pm 1
2a \pm 1 = sqrt(L^2 - a^2)
4a^2 \pm 4a + 1 = L^2 - a^2
5a^2 \pm 4a + 1 = L^2 

(this is literally a Pell equation argh
should have used convergents of \sqrt(5) to find candidates
and kept them if they met the constraints on b)

5a^2 + 0aL -L^2 \pm 4a +0l + 1 = 0
a, l > 0
thank you https://www.alpertron.com.ar/QUAD.HTM
(a_0,l_0) = (0,1) or (0,-1)
an+1 = - 9 ⁢an + 4 ⁢ln \mp 4 ⁢
ln+1 = 20 ⁢an - 9 ⁢ln \pm 8 ⁢

an+1 = - 9 ⁢an - 4 ⁢ln \mp 4 ⁢
ln+1 = - 20 ⁢an - 9 ⁢ln \mp 8 ⁢

*/

#define INT int64_t

int main(int argc, char **argv)
{
    INT a_n, l_n, a_n1, l_n1;

    std::set<INT> solutions;

    // first initial state, first form:

    a_n = 0;
    l_n = 1;

    for(int i = 0; i <= 12; i++) 
    {
        a_n1 = -9 * a_n + 4*l_n -4;
        l_n1 = 20 * a_n - 9*l_n + 8;

        if(a_n1 > 0 && l_n1 > 0) {
            solutions.insert(l_n1);
            std::cout << i << ' ' << a_n1 << ' ' << l_n1 << '\n';
        }

        a_n = a_n1;
        l_n = l_n1;
    }

    // second initial state, first form:

    a_n = 0;
    l_n = -1;

    for(int i = 0; i <= 12; i++) 
    {
        a_n1 = -9 * a_n - 4*l_n -4;
        l_n1 = -20 * a_n - 9*l_n - 8;

        if(a_n1 > 0 && l_n1 > 0) {
            solutions.insert(l_n1);
            std::cout << i << ' ' << a_n1 << ' ' << l_n1 << '\n';
        }

        a_n = a_n1;
        l_n = l_n1;
    }

    // first initial state, second form:

    a_n = 0;
    l_n = 1;

    for(int i = 0; i <= 12; i++) 
    {
        a_n1 = -9 * a_n + 4*l_n +4;
        l_n1 = 20 * a_n - 9*l_n - 8;

        if(a_n1 > 0 && l_n1 > 0) {
            solutions.insert(l_n1);
            std::cout << i << ' ' << a_n1 << ' ' << l_n1 << '\n';
        }

        a_n = a_n1;
        l_n = l_n1;
    }

    // second initial state, first form:

    a_n = 0;
    l_n = -1;

    for(int i = 0; i <= 12; i++) 
    {
        a_n1 = -9 * a_n - 4*l_n +4;
        l_n1 = -20 * a_n - 9*l_n + 8;

        if(a_n1 > 0 && l_n1 > 0) {
            solutions.insert(l_n1);
            std::cout << i << ' ' << a_n1 << ' ' << l_n1 << '\n';
        }

        a_n = a_n1;
        l_n = l_n1;
    }

    std::set<INT>::const_iterator it = solutions.begin();

    INT counter = 0, answer = 0;
    while(counter++<12) {
        std::cout << counter << ' ' << *it << '\n';
        answer += *it;
        it++;
    }

    std::cout << answer << '\n';

    return 0;
}