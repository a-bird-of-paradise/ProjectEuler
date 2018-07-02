
#include <iostream>

int main(int argc, const char * argv[]) {

    // want to know min_n such that #Div(n) >= 1000
    // because if 1/x + 1/y = 1/n then by writing x=n+a and y=n+b we arrive at
    // ab = nn
    // so number of solutions = number of divisors of n*n, /2 (symmetry)
    // so just count the divisors
    // try A019505... hopeless
    
    uint64_t current = 1000-1, i = 1, denoms = 0, max = 0, c2;
    
    bool found = false;
    
    while(!found)
    {
        current+=1;
        c2 = current * current;
        i=1;
        denoms = 0;
        while(i*i<c2)
        {
            if(c2 % i == 0) denoms += 2;
            i+=1;
        }
        if(i*i==c2) denoms += 1;
        if(denoms/2 >= 1000) found = true;
        if(denoms > max)
        {
            max = denoms;
            std::cout << current << "|" << max << std::endl;
        }
    }
    std::cout << current << std::endl;
    return 0;
}
