#include <iostream>
#include <map>

// need at most 14 primes for this ...

const uint64_t nPrimes = 14;
const uint64_t nMax = 4;
const uint64_t Target = 4000000;

struct MapCompare
{
    bool operator()(const std::pair<uint64_t, uint64_t>& left,
                    const std::pair<uint64_t, uint64_t>& right) const
    {
        return left.first < right.first;
    }
} MapComparer;

uint64_t NumUniqueSols(const uint64_t * Seq)
{
    uint64_t Answer = 1;
    
    for(int i = 0; i < nPrimes; i++) Answer *= (2*Seq[i]+1);
    Answer += 1;
    Answer /= 2;
    return Answer;
}

uint64_t Value(const uint64_t * Seq, const uint64_t * Primes)
{
    uint64_t Answer = 1;
    for(int i = 0; i < nPrimes; i++)
    {
        for(int j = 0; j < Seq[i]; j++)
        {
            Answer *= Primes[i];
        }
    }
    return Answer;
}

int main(int argc, const char * argv[]) {
    
    const uint64_t Primes[nPrimes] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43};
          uint64_t Seq   [nPrimes] = {0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    std::map<uint64_t, uint64_t> Answers;
    
    for(int i1 = 0; i1< nMax; i1++)
        for(int i2 = 0; i2<= i1; i2++)
            for(int i3 = 0; i3<= i2; i3++)
                for(int i4 = 0; i4<= i3; i4++)
                    for(int i5 = 0; i5<= i4; i5++)
                        for(int i6 = 0; i6<= i5; i6++)
                            for(int i7 = 0; i7<= i6; i7++)
                                for(int i8 = 0; i8<= i7; i8++)
                                    for(int i9 = 0; i9<= i8; i9++)
                                        for(int i10 = 0; i10<= i9; i10++)
                                            for(int i11 = 0; i11<= i10; i11++)
                                                for(int i12 = 0; i12<= i11; i12++)
                                                    for(int i13 = 0; i13<= i12; i13++)
                                                        for(int i14 = 0; i14<= i13; i14++)
                                                        {
                                                            Seq[0] = i1;
                                                            Seq[1] = i2;
                                                            Seq[2] = i3;
                                                            Seq[3] = i4;
                                                            Seq[4] = i5;
                                                            Seq[5] = i6;
                                                            Seq[6] = i7;
                                                            Seq[7] = i8;
                                                            Seq[8] = i9;
                                                            Seq[9] = i10;
                                                            Seq[10] = i11;
                                                            Seq[11] = i12;
                                                            Seq[12] = i13;
                                                            Seq[13] = i14;
                                                            
                                                            if(NumUniqueSols(Seq) >= Target)
                                                            {
                                                                uint64_t val = Value(Seq,Primes);
                                                                uint64_t Sols = NumUniqueSols(Seq);
                                                                
                                                                Answers[val] = Sols;
                                                            }
                                                        }
    std::cout << Answers.size() << std::endl;
    
    std::pair<uint64_t, uint64_t> TheSolution =
        *std::min_element(Answers.begin(), Answers.end(), MapComparer);
    
    std::cout << TheSolution.first << "|" << TheSolution.second << std::endl;
    
    return 0;
}
