
#include "SplitFuncs.hpp"

std::ostream& operator<<(std::ostream& os, const List& x)
{
    for(List::const_iterator i = x.begin(); i != x.end(); i++)
        std::cout << "{" << *i << "}, ";
    return os;
}

std::ostream& operator<<(std::ostream& os, const ListList& x)
{
    for(ListList::const_iterator i = x.begin(); i != x.end(); i++)
        std::cout << *i << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const PairList& x)
{
    for(PairList::const_iterator i = x.begin(); i != x.end(); i++)
        std::cout << i->first << std::endl << i->second << std::endl << "-----" << std::endl;
    return os;
}

ListList MakePowerSet(const List& x, const bool IncludeNullSet)
{
    uint64_t i, j, bits, i_max;
    List ThisSubset;
    ThisSubset.reserve(InitialCapacity);
    std::vector<List> Answer;
    i_max = 1U << x.size();
    for(i = 0; i < i_max; i++)
    {
        ThisSubset.clear();
        for(bits=i,j=0; bits; bits >>=1, ++j)
        {
            if(bits & 1)
            {
                ThisSubset.push_back(x[j]);
            }
        }
        Answer.push_back(ThisSubset);
    }
    if(!IncludeNullSet) Answer.erase(Answer.begin());
    
    return Answer;
}

PairList MakeAllPairs(const ListList& x)
{
    PairList Answer;
    std::pair<List,List> ThisPair;
    
    for(ListList::const_iterator i = x.begin(); i != x.end(); i++)
    {
        for(ListList::const_iterator j = i; j != x.end(); j++)
        {
            ThisPair.first = *i;
            ThisPair.second = *j;
            Answer.push_back(ThisPair);
        }
    }
    return Answer;
}

PairList DisjointPairs(const PairList& x)
{
    PairList Answer;
    uint64_t seen;
    for(PairList::const_iterator i = x.begin(); i != x.end(); i++)
    {
        seen = 0;
        for(List::const_iterator j = i->first.begin(); j != i->first.end(); j++)
        {
            if(std::find(i->second.begin(), i->second.end(), *j) != i->second.end())
                seen += 1;
        }
        if(seen==0)
            Answer.push_back(*i);
    }
    return Answer;
}

PairList MakeSplitSet(const uint64_t n)
{
    List x;
    x.reserve(InitialCapacity);
    
    for(int i = 0; i < 12; i++) x.push_back(i);
    
    return DisjointPairs(MakeAllPairs(MakePowerSet(x,false)));
}

PairList Peel(const PairList& x, const uint64_t Remove)
{
    PairList answer;
    for(PairList::const_iterator i = x.begin(); i != x.end(); i++)
    {
        if(std::find(i->first.begin(),i->first.end(),Remove) == i->first.end()
           && std::find(i->second.begin(), i->second.end(),Remove) == i->second.end())
        {
            answer.push_back(*i);
        }
    }
    return answer;
}