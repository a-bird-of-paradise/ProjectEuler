#pragma once
#include <vector>

std::vector<std::vector<std::size_t>> GeneratePermutations(std::size_t UpTo)
{
    typedef std::vector<std::size_t> PERMUTATION;
    typedef std::vector<PERMUTATION> ALL_PERMS;
    
    PERMUTATION Element, MutatedElement;
    ALL_PERMS PartialPerm;
    ALL_PERMS Answer, PartialAnswer;
    
    if(UpTo == 0) // return the identity index permutation [0] here
    {
        Element.push_back(0);
        Answer.push_back(Element);
    }
    else
    {
        // get all smaller perms
        PartialAnswer = GeneratePermutations(UpTo - 1);
        // for each smaller perm...
        for(ALL_PERMS::const_iterator i = PartialAnswer.begin();i != PartialAnswer.end();i++)
        {
            Element = *i;
            if(Element.size() == UpTo - 1)
            {
                for(std::size_t j = 0; j <= Element.size(); j++)
                {
                    MutatedElement = Element;
                    MutatedElement.insert(MutatedElement.begin() + j, UpTo-1);
                    Answer.push_back(MutatedElement);
                }
                
            }
            Answer.push_back(Element);
        }
    }
    return Answer;
}
