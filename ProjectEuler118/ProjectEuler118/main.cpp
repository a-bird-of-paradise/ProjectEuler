#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include "MillerRabin.h"
#include "Sieve.h"
#include "SetPartitions.h"
#include "Permutations.h"

//#define NOISY 1



std::vector<std::uint8_t> ApplyPermutationToElement(const std::vector<std::uint8_t>& Element,
                                                     const std::vector<std::size_t>& Permutation)
{
    std::vector<std::uint8_t> Answer;
    
    for(std::vector<std::size_t>::const_iterator i = Permutation.begin(); i != Permutation.end(); ++i)
    {
        Answer.push_back(Element[*i]);
    }
    return Answer;
}

bool IsElementPrime(const std::vector<std::uint8_t>& Element)
{
    
    static std::map<uint32_t,bool> PrimeCache;
    
    uint32_t ToCheck = 0;
    bool Answer;
    
    if(Element.size() == 1)
    {
        if(Element[0] == 2 || Element[0] == 3 || Element[0] == 5 || Element[0] == 7)
            return true;
        else
            return false;
    }
    
    for(std::size_t i = 0; i < Element.size(); ++i)
    {
        ToCheck *= 10;
        ToCheck += Element[i];
    }
    
    std::map<uint32_t,bool>::iterator CacheIt = PrimeCache.find(ToCheck);
    
    if(CacheIt == PrimeCache.end())
    {
        Answer = isprime<uint32_t>(ToCheck);
        PrimeCache[ToCheck] = Answer;
    }
    else
    {
        Answer = CacheIt->second;
    }
    
    return Answer;
}

int main(int argc, const char * argv[]) {

    typedef std::vector<uint8_t> SET;
    typedef std::vector<SET> LIST_OF_SETS;
    typedef std::vector<LIST_OF_SETS> LIST_OF_LIST_OF_SETS;
    
    LIST_OF_LIST_OF_SETS Answer;
    SET ToSplit;
    ToSplit.push_back(1);
    ToSplit.push_back(2);
    ToSplit.push_back(3);
    ToSplit.push_back(4);
    ToSplit.push_back(5);
    ToSplit.push_back(6);
    ToSplit.push_back(7);
    ToSplit.push_back(8);
    ToSplit.push_back(9);
    Answer = GenSplits(ToSplit);

    std::vector<std::vector<std::size_t>> ANS = GeneratePermutations(9);
    
    std::vector<std::vector<std::vector<std::size_t>>> ShreddedPerms;
    
    ShreddedPerms.resize(10);
    
    for(std::vector<std::vector<std::size_t>>::const_iterator i = ANS.begin();
        i != ANS.end();
        i++)
    {
        ShreddedPerms[i->size()].push_back(*i);
    }
    
    /* for each partition... */
    
    int FinalAnswer = 0;
    
    for(LIST_OF_LIST_OF_SETS::const_iterator i = Answer.begin(); i != Answer.end(); ++i)
    {
        int RunningTotalOfPrimes = 1;
        /* for each element of the partition ... */
        for(LIST_OF_SETS::const_iterator j = i->begin(); j != i->end(); ++j)
        {
            int PrimeCount = 0;
            // cannot have 9 digit pandigital prime, so skip that
            //if(j[0].size()==9) { RunningTotalOfPrimes = 0; break; }
            /* for each permutation of the same length as *j... */
            for(std::vector<std::vector<std::size_t>>::const_iterator k = ShreddedPerms[j->size()].begin();
                k != ShreddedPerms[j->size()].end();
                ++k)
            {
                if(IsElementPrime(ApplyPermutationToElement(*j, *k)))
                {
                    PrimeCount++;
                }
            }
            RunningTotalOfPrimes *= PrimeCount;
            if(RunningTotalOfPrimes==0) break;
        }
        FinalAnswer += RunningTotalOfPrimes;
    }
    
    std::cout << FinalAnswer << std::endl;
    
    return 0;
}
