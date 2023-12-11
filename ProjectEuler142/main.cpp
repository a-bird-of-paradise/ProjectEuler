#include <iostream>
#include "Sieve.hpp"    
#include <algorithm>
#include <cmath>
/*
want least x+y+z, x>y>z, such that
x+y = a^2
x-y = b^2
x+z = c^2
x-z = d^2
y+z = e^2
y-z = f^2

so: 2x = a^2 + b^2  -> x = (a^2+b^2) /2 
(a^2+b^2)/2 + y = a^2 -> y = a^2 - x
sim, z = c^2 - x

must have y < x
must have c > sqrt x 

*/

#define INT int64_t
#define LIMIT 1'000LL

int main(int argc, char **argv)
{

    std::cout << "generating squares...\n";

    std::vector<bool> squares(LIMIT*LIMIT,false);
    for(INT i = 0; i < LIMIT; ++i) squares[i*i] = true;

    std::cout << "seeking...\n";

    for(INT a = 3; a < LIMIT; ++a){
        for(INT b = 2; b < LIMIT; ++b){

            INT twox = a*a + b*b;
            if(twox % 2 == 1) continue;
            INT x = twox / 2;
            INT y = a*a - x;
            if(y <= 0 || y >= x) break;

            for(INT c = std::sqrt(x)+1; c < LIMIT; ++c){

                INT z = c*c - x;
                if(z >= y) break; 

                INT dsq = x - z;
                INT esq = y + z;
                INT fsq = y - z;
                
                if(!(squares[dsq] && squares[esq] && squares[fsq])) continue;

                std::cout << '(' << a << ',' << b << ',' << c << ')' << '\n';
                std::cout << "x: " << x << ", y: " << y << ", z: " << z << ", ";
                std::cout << "dd: " << dsq << ", ee: " << esq << ", ff: " << fsq << '\n'; 
                std::cout << x + y + z << '\n';
                goto done;
            }
        }
    }
    done:
    return 0;
}