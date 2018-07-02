#include <iostream>
#include <cmath>
#include <set>
#include <numeric>

typedef uint64_t INT;

INT SumOfSquares(INT n)
{
    return n*(n+1)*(2*n+1)/6;
}

INT Reverse(INT x, const INT base = 10)
{
    INT answer = 0;
    INT remain = 0;
    
    while(x>0)
    {
        remain = x % base;
        answer = (answer * base) + remain;
        x /= base;
    }
    return answer;
}

bool IsPalindrome(INT x, const INT base = 10)
{
    if(x % base == 0) return false;
    return x == Reverse(x, base);
}

int main(int argc, char** argv)
{
    
    const INT lim = 100000000;
    
    INT sqrlim = std::sqrt(lim);
    
    std::set<INT> SSNumbers;
    
    INT temp;
    
    for(INT i = 1; i <= sqrlim; ++i)
    {
        for(INT j = i+1; j <= sqrlim; ++j)
        {
            temp = SumOfSquares(j) - SumOfSquares(i-1);
            
            if(IsPalindrome(temp) && temp < lim)
            {
                SSNumbers.insert(temp);
            }
        }
    }
    
    std::cout << std::accumulate(SSNumbers.begin(), SSNumbers.end(),static_cast<INT>(0)) << std::endl;

    return 0;
}