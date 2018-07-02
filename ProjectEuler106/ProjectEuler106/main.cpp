#include <iostream>
#include <numeric>
#include <chrono>
#include "SplitFuncs.hpp"

bool Domination(const List& a, const List& b)
{
    bool Answer = true;
    bool ADom = true, BDom = true;
    
    for(int i = 0; i < a.size(); i++)
    {
        if(a[i] < b[i]) ADom = false;
        if(b[i] < a[i]) BDom = false;
    }
    
    Answer = ADom || BDom;
    return Answer;
}

int main(int argc, const char * argv[]) {
    
    PairList SplitSet = MakeSplitSet(12);
    List One, Two;
    uint64_t Answer;
    std::size_t OneSize, TwoSize;
    
    std::chrono::time_point<std::chrono::high_resolution_clock> Start, End;
    Start = std::chrono::high_resolution_clock::now();
    
    Answer = 0;
    
    for(auto&& i : SplitSet)
    {
        One.clear();
        Two.clear();
        
        for(auto&& j : i.first) One.push_back(j);
        for(auto&& j : i.second) Two.push_back(j);
        
        std::sort(One.begin(),One.end());
        std::sort(Two.begin(),Two.end());
        
        OneSize = One.size();
        TwoSize = Two.size();
        
        if(OneSize == TwoSize && OneSize >= 2 && !Domination(One,Two))
        {
            Answer++;
        }
    }
    
    std::cout << Answer << std::endl;
    
    End = std::chrono::high_resolution_clock::now();
    
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(End-Start).count() << std::endl;
    
    return 0;
}