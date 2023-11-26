#include <iostream>
#include "Sieve.hpp"    
#include <algorithm>
/*
x^2 - y^2 - z^2 = n^2

ok. 

(x+d)^2 -x^2 -(x-d)^2 
=x^2 +2dx + d^2 -x^2 -(x^2 -2dx +d^2)
= -x^2 +4dx 
so n = x(4d-x) 

ok. x-d > 0 so x > d. 
4d - x > 0 so 4d > x i.e. d > x/4

so x/4 < d < x 

*/

int main(int argc, char **argv)
{

    std::vector<int64_t> answers;
    answers.resize(1'000'000);
    std::fill(std::begin(answers), std::end(answers),0);

    int64_t answer = 0;

    for(int64_t x = 0; x < 1'000'000; x++)
    {
        for(int64_t d = x/4; d < x; d++)
        {
            int64_t n = x*(4*d-x);
            if(n>1'000'000) break;
            if(n>0) answers[n-1]++;
        }
    }

    for(std::size_t i = 0; i < 1'000'000; i++){
        if(answers[i]==10) answer++;
        //std::cout << i+1 << ' ' << answers[i] << '\n';
    }

    std::cout << answer << '\n';

    return 0;
}