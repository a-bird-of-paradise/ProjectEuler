#include <iostream>
#include <iomanip>
#include "Sieve.h"
#include <numeric>
#include <set>


int main(int argc, const char * argv[]) {
    
    // we have 8r_2'(n)-4=420
    // so r_2'(n) = 53
    // write n = 2^{a_0} \prod_i p_i^{2a_i} \prod_j q_j{b_j}
    // where q_j \equiv 1 mod 4 and p_i \equiv 3 mod 4
    // if any a_i half integer then no solutions
    // else define B = \prod_j (1+b_j)
    // if B \equiv 0 mod 2 then r'_2(n) = B/2
    // else r'_2(n) = (B-(-1)^{a_0})/2
    //
    // now n = 2N^2
    // so no a_i are half integral hooray
    //
    // so B = 106 (if B even) or 105 or 107 (depending on parity of a_0)
    // B = 106 says B = 53x2 = (1+52)(1+1)
    // but all b_i even
    // so nope
    // what if B = 107?
    // then sole factor is (1+106) => 5^53 as the minimum form which is far in excess of the limit
    // what if B = 105?
    // then B = 3.5.7 = (1+2)(1+4)(1+6)
    // or also: (3.5).7 or 3.(5.7) or 5.(3.7)
    // i.e. 15.7 or 3.35 or 5.21
    // but n=2N^2
    // so really exponents of 1mod4 primes are 1,2,3
    // or 7,3 or 1,17 or 2,10
    // but all candidates of 1,17 form are at least 5^17.13 > 10^11.
    // so try 1,2,3; 3,7; 2,10 as candidates
    
    std::cout << "Starting..." << std::endl;
    
    const uint64_t LIMIT = 100000000000;
    
    uint64_t PrimeLimit = LIMIT / (5*5*5*13*13);
    
    std::cout << "Generating primes up to " << PrimeLimit << std::endl;
    
    std::vector<uint64_t> Primes = GeneratePrimes(PrimeLimit); // standard eratosthenes method
    
    std::vector<uint64_t> pPrimes, qPrimes;
    
    std::cout << "Shredding into lists (1,3) mod 4" << std::endl;
    
    for(std::vector<uint64_t>::const_iterator i = Primes.begin(); i != Primes.end(); ++i)
    {
        if(*i % 4 == 3) pPrimes.push_back(*i);
        if(*i % 4 == 1) qPrimes.push_back(*i);
    }
    
    std::cout << "Forming all products q_i^3 q_j^2 q_k^1; i,j,k pairwise unequal" << std::endl;
    
    std::vector<uint64_t> qstems;
    uint64_t istem, jstem, kstem; // 3,2,1
    uint64_t istem2, jstem2;      // 3,7
    uint64_t istem3, jstem3;      // 2,10
    
    for(std::vector<uint64_t>::const_iterator i = qPrimes.begin(); i != qPrimes.end(); ++i)
    {
        istem = (*i)*(*i)*(*i);
        if(istem <= LIMIT)
        {
            for(std::vector<uint64_t>::const_iterator j = qPrimes.begin(); j != qPrimes.end(); ++j)
            {
                if(*j == *i) continue;
                jstem = istem * (*j)*(*j);
                if(jstem <= LIMIT)
                {
                    for(std::vector<uint64_t>::const_iterator k = qPrimes.begin(); k != qPrimes.end(); ++k)
                    {
                        if(*k == *i || *k == *j) continue;
                        kstem = *k * jstem;
                        if(kstem <=LIMIT)
                        {
                            qstems.push_back(kstem);
                        }
                    }
                }
            }
        }
    }
    std::cout << "forming products q_i^3 q_j^7" << std::endl;
    for(std::vector<uint64_t>::const_iterator i = qPrimes.begin(); i != qPrimes.end(); ++i)
    {
        istem2 = (*i)*(*i)*(*i);
        if(istem2 <= LIMIT)
        {
            for(std::vector<uint64_t>::const_iterator j = qPrimes.begin();
                j != qPrimes.end() && *j < std::pow(LIMIT,1.0/7.0);
                ++j)
            {
                if(*j == *i) continue;
                jstem2 = istem2 * (*j)*(*j) * (*j)*(*j) * (*j)*(*j) * (*j);
                if(jstem2 <= LIMIT)
                {
                    qstems.push_back(jstem2);
                }
            }
        }
    }
    std::cout << "forming products q_i^2 q_j^10" << std::endl;
    for(std::vector<uint64_t>::const_iterator i = qPrimes.begin(); i != qPrimes.end(); ++i)
    {
        istem3 = (*i)*(*i);
        if(istem3 <= LIMIT)
        {
            for(std::vector<uint64_t>::const_iterator j = qPrimes.begin();
                j != qPrimes.end() && *j < std::pow(LIMIT,1.0/10.0);
                ++j)
            {
                if(*j == *i) continue;
                jstem3 = istem3 * (*j)*(*j) * (*j)*(*j) * (*j)*(*j) * (*j)*(*j)* (*j)*(*j);
                if(jstem3 <= LIMIT)
                {
                    qstems.push_back(jstem3);
                }
            }
        }
    }
    
    std::set<uint64_t> dedup;
    
    for(auto& i: qstems) dedup.insert(i);
    
    qstems.clear();
    
    for(auto& i: dedup) qstems.push_back(i);
    
    /*
    std::cout << qstems.size() << std::endl;
    
    std::cout << *std::max_element(qstems.begin(), qstems.end()) << std::endl;
    std::cout << *std::min_element(qstems.begin(), qstems.end()) << std::endl;
    */
    std::sort(qstems.begin(),qstems.end());
    
    std::cout << "Calculating all possible p fronts (plus 2s)" << std::endl;
    
    uint64_t pLimit = LIMIT / *std::min_element(qstems.begin(), qstems.end());
    uint64_t temp;
    
    pPrimes.push_back(2);
    
    std::sort(pPrimes.begin(),pPrimes.end());
    
    std::vector<uint64_t> pFronts;
    
    std::set<uint64_t> FrontP, FrontPCopy;
    
    FrontP.insert(1);
    
    std::size_t precount,postcount;
    
    precount = FrontP.size();
    
    postcount = precount + 1;
    
    while(precount != postcount)
    {
        precount = FrontP.size();
        FrontPCopy = FrontP;
        for(std::set<uint64_t>::const_iterator i = FrontP.begin(); i != FrontP.end(); ++i)
        {
            for(std::vector<uint64_t>::const_iterator j = pPrimes.begin(); j != pPrimes.end(); ++j)
            {
                temp = (*i) * (*j);
                if(temp <= pLimit) FrontPCopy.insert(temp);
                else break;
            }
        }
        FrontP=FrontPCopy;
        postcount = FrontP.size();
    }
    
    for(std::set<uint64_t>::const_iterator i = FrontP.begin(); i != FrontP.end(); ++i)
    {
        pFronts.push_back(*i);
    }
    
    std::cout << "Generating answers" << std::endl;
    
    std::vector<uint64_t> Answers;
    
    std::sort(pFronts.begin(),pFronts.end());
    std::sort(qstems.begin(),qstems.end());
    
    for(std::vector<uint64_t>::const_iterator i = pFronts.begin(); i != pFronts.end(); ++i)
    {
        for(std::vector<uint64_t>::const_iterator j = qstems.begin(); j != qstems.end(); ++j)
        {
            temp = (*i)*(*j);
            if(temp <= LIMIT)
            {
                Answers.push_back(temp);
            }
            else
            {
                break;
            }
        }
    }
    
    std::cout << "Enumerating solution" << std::endl;
    
    long double TheAnswer = 0;
    
    std::cout <<
        std::fixed <<
        std::setprecision(0) <<
        std::accumulate(Answers.begin(), Answers.end(), TheAnswer) <<
        std::endl;
    
    return 0;
}
