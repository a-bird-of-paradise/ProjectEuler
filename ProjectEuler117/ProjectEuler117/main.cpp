#include <iostream>
#include <vector>

template<typename T>
T Tetranacci(uint64_t n)
{
    int64_t i = 2, j;
    std::vector<T> Tetras;
    Tetras.reserve(n+1);
    Tetras.push_back(0); // so tetranacci[0] == 0
    Tetras.push_back(1); // so tetranacci[1] == 1
    //Tetras.push_back(2); // so tetranacci[2] == 2
    //Tetras.push_back(4); // so tetranacci[3] == 3
    //Tetras.push_back(8); // so tetranacci[4] == 4
    T answer = 0;
    
    while(i <= n)
    {
        answer = 0;
        j = (i-4) < 0 ? 0 : i-4;
        answer += Tetras[j];
        
        j = (i-3) < 0 ? 0 : i-3;
        answer += Tetras[j];
        
        j = (i-2) < 0 ? 0 : i-2;
        answer += Tetras[j];
        
        j = (i+1) < 0 ? 0 : i-1;
        answer += Tetras[j];
        
        Tetras.push_back(answer);
        ++i;
    }
    
    return answer;
}

int main(int argc, const char * argv[]) {

    //uint64_t x;
    
    //for(x = 0; x <= 51; x++)
    //    std::cout << x << "|" << Tetranacci<uint64_t>(x) << std::endl;
    
    std::cout << Tetranacci<uint64_t>(51) << std::endl;
    
    return 0;
}
