#include <iostream>
#include "Sieve.hpp"    
#include <algorithm>
#include <cmath> 
#include <set>
/*

sequence is 1,4,5,9,14,23,37,60,...

per OEIS this is A000285
has a GF of (1+3*x)/(1-x-x^2)
but really (x+3x^2)(1-x-x^2) due to the powers of x

so: a - ax - ax^2 = x + 3x^2
(3+a)x^2 + (1+a) x - a = 0 

x = -(1+a)/(6+2a) \pm \sqrt( 1 + 2a + a^2 +4a(3+a)) 
thing in square root is some perfect square, k

1 + 14a + 5a^2 = k^2
5 + 70a +25a^2 = 5k^2
(5a+7)^2 -5k^2 = 44
X^2 - 5Y^2 = 44
thank you https://www.alpertron.com.ar/QUAD.HTM

initial states: (7,1), (13,5), (8,2) (all \pm variants i.e. 12 states)

recurse:
x_n1 = 9x_n + 20y_n
y_n1 = 4x_n +  9y_n

x_n1 = 9x_n - 20y_n
y_n1 =-4x_n +  9y_n

P,Q,R,S
*/

#define INT int64_t

void stepper(INT x_0, INT y_0, INT P, INT Q, INT R, INT S, int n, std::set<INT>& sols)
{
    INT x_n1, y_n1, x_n, y_n;

    x_n = x_0;
    y_n = y_0;

    for(int i = 0; i <= n; i++)
    {
        x_n1 = P*x_n + Q*y_n;
        y_n1 = R*x_n + S*y_n;

        if( (x_n1 - 7) % 5 == 0 && x_n1 > 7)
            sols.insert((x_n1-7)/5);

        x_n = x_n1;
        y_n = y_n1;
    }
}

int main(int argc, char **argv)
{
    INT a_n, l_n, a_n1, l_n1;

    std::set<INT> solutions;
/*
    initial states: (7,1), (13,5), (8,2) (all \pm variants i.e. 12 states)

recurse:
x_n1 = 9x_n + 20y_n
y_n1 = 4x_n +  9y_n

x_n1 = 9x_n - 20y_n
y_n1 =-4x_n +  9y_n
*/
    stepper(7,1,9,20,4,9,30,solutions);
    stepper(7,-1,9,20,4,9,30,solutions);
    stepper(-7,1,9,20,4,9,30,solutions);
    stepper(-7,-1,9,20,4,9,30,solutions);
    stepper(7,1,9,-20,-4,9,30,solutions);
    stepper(7,-1,9,-20,-4,9,30,solutions);
    stepper(-7,1,9,-20,-4,9,30,solutions);
    stepper(-7,-1,9,-20,-4,9,30,solutions);

    stepper(13,5,9,20,4,9,30,solutions);
    stepper(13,-5,9,20,4,9,30,solutions);
    stepper(-13,5,9,20,4,9,30,solutions);
    stepper(-13,-5,9,20,4,9,30,solutions);
    stepper(13,5,9,-20,-4,9,30,solutions);
    stepper(13,-5,9,-20,-4,9,30,solutions);
    stepper(-13,5,9,-20,-4,9,30,solutions);
    stepper(-13,-5,9,-20,-4,9,30,solutions);

    stepper(8,2,9,20,4,9,30,solutions);
    stepper(8,-2,9,20,4,9,30,solutions);
    stepper(-8,2,9,20,4,9,30,solutions);
    stepper(-8,-2,9,20,4,9,30,solutions);
    stepper(8,2,9,-20,-4,9,30,solutions);
    stepper(8,-2,9,-20,-4,9,30,solutions);
    stepper(-8,2,9,-20,-4,9,30,solutions);
    stepper(-8,-2,9,-20,-4,9,30,solutions);


    std::set<INT>::const_iterator it = solutions.begin();
    INT counter = 0, answer = 0;

    while(counter < 30)
    {
        answer += *it;
        it++;
        counter++;
    }

    std::cout << answer << '\n';

    return 0;
}