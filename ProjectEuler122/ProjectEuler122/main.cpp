#include <iostream>
#include <limits>
#include <vector>
#include <set> // tried - slows down too much

#include <assert.h>

typedef int16_t INT;

typedef std::vector<INT> Addition_Chain;

typedef std::vector<Addition_Chain> Chain_List;

void AppendList(Chain_List& Base, const Chain_List& ToAppend)
{
    for(Chain_List::const_iterator i = ToAppend.begin();
        i != ToAppend.end();
        ++i)
    {
        Base.push_back(*i);
    }
}

Chain_List NextBrauerChains(const Addition_Chain& Base)
{
    assert(Base.size() >= 1);
    
    Addition_Chain Root;
    
    Chain_List Answer;
    
    for(Addition_Chain::const_iterator i = Base.begin();
        i != Base.end();
        ++i)
    {
        Root = Base;
        //std::sort(Root.begin(), Root.end());
        Root.push_back(*i + Root.back());
        //std::sort(Root.begin(), Root.end());
        Answer.push_back(Root);
    }
    
    return Answer;
}

Chain_List AllPossibleBrauerChains(const INT& MaxDepth)
{
    assert(MaxDepth>=1);
    
    INT current_depth = 1;
    
    Chain_List answer, current_level_chains, next_level_chains;
    
    Addition_Chain current_chain;
    current_chain.push_back(1);
    answer.push_back(current_chain);
    
    while(current_depth <= MaxDepth)
    {
        current_level_chains.clear();
        next_level_chains.clear();
        for(Chain_List::const_iterator i = answer.begin();
            i != answer.end();
            ++i)
        {
            if(i->size() == current_depth)
            {
                current_level_chains.push_back(*i);
            }
        }
        
        for(Chain_List::const_iterator i = current_level_chains.begin();
            i != current_level_chains.end();
            ++i)
        {
            AppendList(next_level_chains, NextBrauerChains(*i));
        }
        
        AppendList(answer, next_level_chains);
        
        current_depth++;
    }
    
    return answer;
    
}

Addition_Chain ShortestBrauerChain(const INT& n)
{
    assert(n>=1);
    Addition_Chain answer;
    Chain_List candidates, priorcandidates;
    
    bool FoundIt = false;
    
    answer.push_back(1);
    
    if(n >= 2)
    {
        answer.push_back(2);
        candidates.push_back(answer);
    }
    
    if(n >= 3)
    {
        while(!FoundIt)
        {
            priorcandidates=candidates;
            candidates.clear();
            for(Chain_List::const_iterator i = priorcandidates.begin();
                i != priorcandidates.end();
                ++i)
            {
                AppendList(candidates, NextBrauerChains(*i));
            }
            
            for(Chain_List::const_iterator i = candidates.begin();
                i != candidates.end();
                ++i)
            {
                if(i->back() == n)
                {
                    FoundIt = true;
                    answer = *i;
                    break;
                }
            }
        }
        
    }
    return answer;
}

std::ostream& operator<<(std::ostream& lhs, const Addition_Chain& rhs)
{
    lhs << "[";
    for(std::size_t i = 0; i < rhs.size(); ++i)
    {
        lhs << rhs[i];
        if(i < rhs.size() - 1) lhs << ",";
    }
    lhs << "]";
    return lhs;
}

INT m(const INT& n) { return ShortestBrauerChain(n).size() - 1; }

int main(int argc, char **argv)
{
    /* method one: takes a long time (2 mins) but correct
    INT answer = 0, temp;
    
    for(INT i = 1; i <= 200; ++i)
    {
        temp = m(i);
        answer += temp;
        std::cout << i << "|" << temp << "|" << answer << std::endl;
    }
    */
    
    // this way works within a minute
    
    Chain_List AllChains = AllPossibleBrauerChains(10);
    
    INT mins[201], temp;
    
    for(std::size_t i = 0; i <= 200; ++i) mins[i] = std::numeric_limits<INT>::max();
    
    for(Chain_List::const_iterator i = AllChains.begin();
        i != AllChains.end();
        ++i)
    {
        temp = i->back();
        if(temp <= 200)
        {
            if(mins[temp] > i->size() - 1)
            {
                mins[temp] = i->size() - 1;
            }
        }
    }
    
    temp = 0;
    
    for(std::size_t i = 1; i <= 200; ++i)
    {
        
        // optimisation: can go one lower in the AllChains call
        // and if any mins[i] = std::numeric_limits<INT>::max()
        // then mins[i] = mins[i-1]+1
        // lets us vastly reduce comp time (to 2.7s)
        
        if(mins[i] == std::numeric_limits<INT>::max())
        {
            mins[i] = mins[i-1]+1;
        }
        
        temp += mins[i];
        
        std::cout << i << "|" << mins[i] << "|" << temp << std::endl;
    }
    
    return 0;
}