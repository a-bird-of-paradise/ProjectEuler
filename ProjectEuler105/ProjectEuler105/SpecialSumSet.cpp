#include "SpecialSumSet.hpp"
#include <numeric>

bool IsSpecialSumSet(const List& TheSet, const PairList& Splitter)
{
    bool Answer = true;
    
    List One,Two;
    uint64_t OneSum, TwoSum;
    std::size_t OneSize, TwoSize;
    
    for(PairList::const_iterator i = Splitter.begin(); i != Splitter.end(); i++)
    {
        One.clear();
        Two.clear();
        for(List::const_iterator j = i->first.begin(); j != i->first.end(); j++)
            One.push_back(TheSet[*j]);
        for(List::const_iterator j = i->second.begin(); j != i->second.end(); j++)
            Two.push_back(TheSet[*j]);
        
        OneSum = std::accumulate(One.begin(),One.end(), 0);
        TwoSum = std::accumulate(Two.begin(),Two.end(), 0);
        
        OneSize = One.size();
        TwoSize = Two.size();
        
        if( (OneSize > TwoSize && OneSum < TwoSum)
            || (TwoSize > OneSize && TwoSum < OneSum)
           || OneSum == TwoSum)
        {
            Answer = false ; break;
        }
    }
    
    if(TheSet.size() == 12 and Answer == true) std::cout << TheSet << std::endl;
    
    return Answer;
}
