#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <numeric>
#include <chrono>

#include "SplitFuncs.hpp"
#include "SpecialSumSet.hpp"

int main(int argc, const char * argv[]) {
    
    std::chrono::time_point<std::chrono::high_resolution_clock> Start, End;
    
    Start = std::chrono::high_resolution_clock::now();
    
    PairList SplitSeven,SplitEight,SplitNine,SplitTen,SplitEleven,SplitTwelve;
    
    SplitTwelve = MakeSplitSet(12);
    SplitEleven = Peel(SplitTwelve,11);
    SplitTen = Peel(SplitEleven,10);
    SplitNine = Peel(SplitTen,9);
    SplitEight = Peel(SplitNine,8);
    SplitSeven = Peel(SplitEight,7);
    
    std::ifstream data("/Users/markdouglas/sets.txt");
    
    std::string line;
    List Items;
    std::string Item;
    
    uint64_t Result = 0;
    
    while(std::getline(data,line))
    {
        Items.clear();
        std::istringstream iss(line);
        while(std::getline(iss,Item,','))
        {
            Items.push_back(std::stoi(Item));
        }
        
        bool Answer;
        
        switch(Items.size())
        {
            case 7: Answer = IsSpecialSumSet(Items,SplitSeven); break;
            case 8: Answer = IsSpecialSumSet(Items,SplitEight); break;
            case 9: Answer = IsSpecialSumSet(Items,SplitNine); break;
            case 10: Answer = IsSpecialSumSet(Items,SplitTen); break;
            case 11: Answer = IsSpecialSumSet(Items,SplitEleven); break;
            case 12: Answer = IsSpecialSumSet(Items,SplitTwelve); break;
            default: Answer = false;
        }
        
        if(Answer) Result += std::accumulate(Items.begin(),Items.end(),0);
        
    }
    std::cout << Result << std::endl;
    
    End = std::chrono::high_resolution_clock::now();
    
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(End-Start).count() << std::endl;
    
    return 0;
}
