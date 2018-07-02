#pragma once

#include <iostream>
#include <vector>

template<typename T>
void PartitionPrint(const std::vector<std::vector<T>>& ToPrint, int Level)
{
    if(Level != 0) std::cout << '[' << Level << ']';
    for(typename std::vector<std::vector<T>>::const_iterator i = ToPrint.begin();
        i!= ToPrint.end();
        i++)
    {
        for(typename std::vector<T>::const_iterator j = i->begin(); j != i->end(); j++)
        {
            std::cout << *j;
        }
        std::cout << "|";
    }
    std::cout << std::endl;
}

template<typename T>
std::vector<std::vector<std::vector<T>>> GenSplits(std::vector<T> ToSplit,
                                                   int Level = 1)
{
    typedef std::vector<T> SET;
    typedef std::vector<SET> LIST_OF_SETS;
    typedef std::vector<LIST_OF_SETS> LIST_OF_LIST_OF_SETS;
    
    LIST_OF_LIST_OF_SETS Answer, SubAnswer;
    LIST_OF_SETS PartialPartition, MutatedPartition;
    SET Singleton, Element;
    
    T Item;
    
    if(ToSplit.empty()) // return the empty set if passed nothing
    {
        Singleton.clear();
        PartialPartition.push_back(Singleton); // empty
        Answer.push_back(PartialPartition);
    }
    if(ToSplit.size() == 1) // the only partition of {x} is {x}
    {
        Item = ToSplit.back();
        Singleton.clear();
        Singleton.push_back(Item);
        PartialPartition.push_back(Singleton);
        Answer.push_back(PartialPartition);
    }
    else // recurse for size >= 2
    {
        Item = ToSplit.back();
        ToSplit.pop_back();
        SubAnswer = GenSplits(ToSplit, Level+1);
        for(typename LIST_OF_LIST_OF_SETS::iterator i = SubAnswer.begin(); i != SubAnswer.end(); i++)
        {
            // case 1: add the singleton to complete the partial partitions
            PartialPartition = *i;
            Singleton.clear();
            Singleton.push_back(Item);
            PartialPartition.push_back(Singleton);
            Answer.push_back(PartialPartition);
#ifdef NOISY
            PartitionPrint(PartialPartition,Level);
#endif
            // case 2: add the singleton to an element of the partial partition
            
            for(typename LIST_OF_SETS::iterator j = i->begin(); j != i->end(); j++)
            {
                Element = *j;
                // remove element from copy of *i
                MutatedPartition = *i;
                MutatedPartition.erase(std::remove(MutatedPartition.begin(),
                                                   MutatedPartition.end(),
                                                   Element),
                                       MutatedPartition.end());
                // add singleton to element
                Element.push_back(Item);
                MutatedPartition.push_back(Element);
                Answer.push_back(MutatedPartition);
#ifdef NOISY
                PartitionPrint(MutatedPartition,Level);
#endif
            }
            
        }
    }
    return Answer;
}


