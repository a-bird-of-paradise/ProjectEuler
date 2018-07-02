#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>

bool IsBitSet(uint64_t num, uint64_t bit)
{
    return 1 == ( (num >> bit) & 1);
}

int main(int argc, const char * argv[]) {
    
    // ok how far are we going?
    
    uint64_t NCOLS = 15;
    uint64_t NROWS = std::pow(2,NCOLS);
    
    std::vector<uint64_t> inner;
    
    for(std::size_t j = 0; j < NCOLS; j++) inner.push_back(0);
    
    std::vector<std::vector<uint64_t>> Successes;
    
    for(std::size_t i = 0; i < NROWS; i++)
    {
        Successes.push_back(inner);
    }
    
    for(uint64_t i = 0; i < NROWS; i++)
    {
        for(uint64_t j = 0; j < NCOLS; j++)
        {
            Successes[i][j] = IsBitSet(i, j);
        }
    }
    
    inner.clear();
    uint64_t result = 0;
    uint64_t answer = 0, denom = 1;
    
    for(uint64_t i = 0; i < NROWS; i++)
    {
        result = std::accumulate(Successes[i].begin(), Successes[i].end(),0);
        if(result > NCOLS/2)
        {
            inner.push_back(i);
        }
    }
    
    for(std::vector<uint64_t>::const_iterator i = inner.begin();
        i != inner.end();
        ++i)
    {
        result = 1;
        for(uint64_t j = 0; j < NCOLS; j++)
        {
            if(Successes[*i][j] == 0)
                result *= (j)+1;
        }
        answer += result;
    }
    
    for(uint64_t i = 1; i <= NCOLS+1; i++) denom *= i;
    
    std::cout << answer << "|" << denom << "|" << denom/answer << std::endl;
    
    return 0;
}
