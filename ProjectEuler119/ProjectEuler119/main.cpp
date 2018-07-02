#include <iostream>
#include <gmpxx.h>
#include <vector>

//typedef mpz_class INT;
typedef uint64_t INT;

typedef std::vector<INT> PARTITION;
typedef std::vector<PARTITION> PARTITIONS_OF_A_NUMBER;
typedef std::vector<PARTITIONS_OF_A_NUMBER> ALL_PARTITIONS;

const INT MAX_POWER = 13;
const INT MAX_BASE = 68; // 70 works

template<typename T>
bool IsGreaterThan(const T& Left, const T& Right)
{
    return Left > Right;
}

ALL_PARTITIONS ExtendPartitions(const ALL_PARTITIONS& OneSmaller)
{
    ALL_PARTITIONS Answer;
    PARTITIONS_OF_A_NUMBER Element;
    PARTITION ThisPartition;
    
    std::size_t n = OneSmaller.size();
    
    std::cout << "!!!" << n << std::endl;
    
    // base case: n = 0, return the single partition
    
    if(n == 0)
    {
        ThisPartition.push_back(1);
        Element.push_back(ThisPartition);
        Answer.push_back(Element);
    }
    else
    {
        
        // and also add the singleton
        
        ThisPartition.clear();
        ThisPartition.push_back(n+1);
        Element.push_back(ThisPartition);
        
        // ok - for each element of OneSmaller...
        
        for(std::size_t i = 0; i < OneSmaller.size(); ++i)
        {
            // for each partition of i+1...
            for(PARTITIONS_OF_A_NUMBER::const_iterator j = OneSmaller[i].begin();
                j!=OneSmaller[i].end();
                ++j)
            {
                // add n - i to the partition and push onto element
                // but only where this would form a nonincreasing sequence
                if(n-i <= j->back())
                {
                    ThisPartition = *j;
                    ThisPartition.push_back(n - i);
                    Element.push_back(ThisPartition);
                }
            }
        }
        
        Answer = OneSmaller;
        Answer.push_back(Element);
        
    }
    return Answer;
}

void PrintPartitions(const ALL_PARTITIONS& ToPrint)
{
    for(std::size_t i = 0; i < ToPrint.size(); ++i)
    {
        std::cout << ToPrint[i].size() << " Partitions of " << i+1 << std::endl;
        for(PARTITIONS_OF_A_NUMBER::const_iterator j = ToPrint[i].begin();
            j != ToPrint[i].end();
            ++j)
        {
            for(PARTITION::const_iterator k = j->begin(); k != j->end(); ++k)
            {
                std::cout << *k << "|";
            }
            std::cout << std::endl;
        }
    }
}

template<typename T, typename SRC>
std::vector<T> ShredIntoVector(const SRC& ShredMe)
{
    SRC remainder, Shredded;
    std::vector<T> Answer;
    
    Shredded = ShredMe;
    while(Shredded != 0)
    {
        remainder = Shredded % 10;
        Shredded /= 10;
        Answer.push_back(mpz_get_ui(remainder.get_mpz_t()));
    }
    return Answer;
}

int main(int argc, const char * argv[]) {
    
    PARTITION x, Shredded;
    PARTITIONS_OF_A_NUMBER y;
    ALL_PARTITIONS z;
    
    INT I = 0;
    
    mpz_class CurrentBase;
    std::vector<mpz_class> Answers;
    
    while(++I <= MAX_BASE)
    {
        z = ExtendPartitions(z);
    }
    
    //PrintPartitions(z);
    
    std::size_t i;
    
    for(i = 1; i <= MAX_BASE; ++i)
    {
        CurrentBase = 1;
        for(INT j = 1; j <= MAX_POWER; ++j)
        {
            CurrentBase *= i;
            if(CurrentBase >= 10)
            {
                Shredded = ShredIntoVector<uint64_t,mpz_class>(CurrentBase);
                Shredded.erase(std::remove(Shredded.begin(),Shredded.end(),0),Shredded.end());
                std::sort(Shredded.begin(), Shredded.end(),IsGreaterThan<INT>);
            
                /*std::cout << "_" << CurrentBase << "|" << j << std::endl;
                 for(PARTITION::const_iterator k = Shredded.begin(); k != Shredded.end(); ++k)
                 std::cout << *k << "|";
                 std::cout << std::endl;
                 */
                if(std::find(z[i-1].begin(),z[i-1].end(),Shredded) != z[i-1].end())
                {
                    std::cout << i << "|" << j << "|" << CurrentBase << std::endl;
                    Answers.push_back(CurrentBase);
                }
            }
        }
    }
    
    std::sort(Answers.begin(), Answers.end());
    
    for(i = 0; i < Answers.size(); ++i)
    {
        std::cout << i+1 << "|" << Answers[i] << std::endl;
    }
    
    return 0;
}
