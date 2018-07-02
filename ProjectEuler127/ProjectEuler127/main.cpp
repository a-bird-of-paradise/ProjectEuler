#include <iostream>
#include <map>
#include <cmath>
#include <set>

#include "Sieve.h"

typedef uint64_t INT;

const INT limit = 120000;

const INT limit_sqrt = static_cast<INT>(std::sqrt(limit));

typedef std::vector<INT> List;

typedef std::vector<List> ListList;

typedef std::vector<std::pair<INT,INT>> PairList;

typedef std::tuple<INT,INT,INT> Triple;

typedef std::set<Triple> TripleList;

const List Primes = GeneratePrimes(limit);

const List Radicals = GenerateRadicals(limit);

List FactorsOfRadical(INT Radical)
{
    List Factors;
    
    List::const_iterator ThisPrime = Primes.begin();
    
    if(Radical == 1)
    {
        Factors.push_back(Radical);
    }
    else if(std::binary_search(Primes.begin(), Primes.end(), Radical))
    {
        Factors.push_back(Radical);
    }
    else
    {
        while(Radical > 0 && ThisPrime != Primes.end())
        {
            if(Radical % *ThisPrime == 0)
            {
                Radical /= *ThisPrime;
                Factors.push_back(*ThisPrime);
            }
            
            ++ThisPrime;
        }
    }
    return Factors;
}

List AllPowersOfProduct_Inner(const List Factors,
                              const INT UpTo,
                              const List CurrentPowers,
                              const std::size_t index)
{
    List Answer, ThisPower, ThisAnswer;
    
    if(index < Factors.size())
    {
        INT CurrValue = 1;
        
        for(std::size_t i = 0; i < Factors.size(); i++) CurrValue *= std::pow(Factors[i], CurrentPowers[i]);
        
        if(CurrValue < UpTo)
        {
            // this index is bigger...
            
            Answer.push_back(CurrValue);
            
            ThisPower = CurrentPowers;
        
            ThisPower[index]++;
            
            ThisAnswer = AllPowersOfProduct_Inner(Factors, UpTo, ThisPower, index);
            
            for(auto&& i : ThisAnswer) Answer.push_back(i);
            
            // or the next one is
            
            ThisAnswer = AllPowersOfProduct_Inner(Factors, UpTo, CurrentPowers, index + 1);
            
            for(auto&& i : ThisAnswer) Answer.push_back(i);
        }
    }
    return Answer; // empty list at end of tree
}

List AllPowersOfProduct(const List Factors, const INT UpTo)
{
    List Answers, defaults;
    
    for(auto&& i : Factors)
    {
        defaults.push_back(i/i);
    }
   
    if(Factors.size() == 1 && Factors[0] == 1)
    {
        Answers.push_back(1);
    }
    else
    {
        Answers = AllPowersOfProduct_Inner(Factors, UpTo, defaults,0);
    }
    
    std::sort(Answers.begin(),Answers.end());
    Answers.erase(std::unique(Answers.begin(),Answers.end()),Answers.end());
    
    return Answers;
}

int main(int argc, const char** argv){
    
    List SquareFree = GenerateSquareFreeNumbers(limit_sqrt+1);
    
    std::map<INT,List> Rads;
    
    for(auto&& i : SquareFree)
    {
        for(auto&& j : SquareFree)
        {
            if(j <= limit / (i*i) && i <= j && are_comprimes(i, j))
            {
                Rads[i].push_back(j);
            }
        }
    }
    
    std::map<INT,List> Candidates;
    
    for(auto&& i : Rads)
    {
        std::cout << i.first << std::endl;
        List FirstPossibles = AllPowersOfProduct(FactorsOfRadical(Radicals[i.first]),limit);
        
        for(auto&& j : FirstPossibles)
        {
            for(auto&& k : i.second)
            {
                List SecondPossibles = AllPowersOfProduct(FactorsOfRadical(Radicals[k]),limit);
                for(auto&& l : SecondPossibles)
                {
                    Candidates[std::min(j,l)].push_back(std::max(j,l));
                }
            }
        }
    }
    
    TripleList abcs;
    
    INT a,b,c, small, middle, large;
    
    for(auto&& i : Candidates)
    {
        for(auto&& j : i.second)
        {
            a = i.first;
            b = j;
            c = a + b;
            
            if(c < limit
               && Radicals[a]*Radicals[b]*Radicals[c] < c
               && are_comprimes(a,c))
               //&& are_comprimes(b, c))// necessarily true!
            {
                abcs.insert(std::make_tuple(a,b,c));
            }
            
            if(a > b)
            {
                c = a - b;
            }
            else
            {
                c = b - a;
            }
            
            small = std::min(a,std::min(b,c));
            large = std::max(std::max(a,b),c);
            
            if(a != small && a != large)
            {
                middle = a;
            }
            else if(b != small && b != large)
            {
                middle = b;
            }
            else
            {
                middle = c;
            }
            
            a = small;
            b = middle;
            c = large;
            
            if(c < limit
               && Radicals[a]*Radicals[b]*Radicals[c] < c
               && are_comprimes(a,c))
              // && are_comprimes(b, c) ) // necessarily true!
            {
                abcs.insert(std::make_tuple(a,b,c));
            }
            
        }
    }
    
    INT accum = 0;
    
    for(auto&& i : abcs)
    {
        accum += std::get<2>(i);
    }
    
    std::cout << abcs.size() << std::endl;
    std::cout << accum << std::endl;
    
    //18407904
    
    return 0;
}