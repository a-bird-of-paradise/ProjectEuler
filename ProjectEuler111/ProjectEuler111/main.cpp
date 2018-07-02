#include <iostream>
#include <vector> 
#include <numeric>

const int NumDigits = 10;

void PrintVec(const std::vector<std::size_t>& ToPrint)
{
    for(std::vector<std::size_t>::const_iterator i = ToPrint.begin(); i != ToPrint.end(); i++)
        std::cout << *i;
    std::cout << std::endl;
}

 // Miller-Rabin stuff
typedef unsigned long long ULL;
typedef long long LL;

LL MultiplyMod(LL a, LL b, LL mod) { //computes a * b % mod
    ULL r = 0;
    a %= mod, b %= mod;
    while (b) {
        if (b & 1) r = (r + a) % mod;
        b >>= 1, a = ((ULL) a << 1) % mod;
    }
    return r;
}

template<typename T>
T PowerMod(T a, T n, T mod) {  //computes a^n % mod
    T r = 1;
    while (n) {
        if (n & 1) r = MultiplyMod(r, a, mod);
        n >>= 1, a = MultiplyMod(a, a, mod);
    }
    return r;
}

template<typename T>
bool isprime(T n) { //determines if n is a prime number
    const int pn = 5, p[] = { 2, 3, 5, 7, 11 }; //, 13, 17, 19, 23 }; // speed up: don't use too many primes
    for (int i = 0; i < pn; ++i)
        if (n % p[i] == 0) return n == p[i];
    if (n < p[pn - 1]) return 0;
    T s = 0, t = n - 1;
    while (~t & 1)
        t >>= 1, ++s;
    for (int i = 0; i < pn; ++i) {
        T pt = PowerMod<T> (p[i], t, n);
        if (pt == 1) continue;
        bool ok = 0;
        for (int j = 0; j < s && !ok; ++j) {
            if (pt == n - 1) ok = 1;
            pt = MultiplyMod(pt, pt, n);
        }
        if (!ok) return 0;
    }
    return 1;
}

bool CheckVector(const std::vector<std::size_t>& ToCheck)
{
    if(ToCheck[0] == 0) return false;
    int64_t n = 0;
    for(std::vector<std::size_t>::const_iterator i = ToCheck.begin(); i != ToCheck.end(); i++)
    {
        n *= 10;
        n += *i;
    }
    return isprime(n);
}

bool IsIncreasing(const std::vector<std::size_t>& ToCheck)
{
    bool Answer = true;
    if (ToCheck.size() > 1)
    {
        std::vector<std::size_t>::const_iterator i = ToCheck.begin();
        std::size_t last = *i;
        i++;
        std::size_t next = *i;
        while(i != ToCheck.end() && Answer == true)
        {
            Answer = next > last;
            last = next;
            i++;
            next = *i;
        }
    }
    return Answer;
}


bool GenerateNext(std::vector<std::size_t>& ToProcess) // gives the next permutation to use
{
    std::size_t WorkIndex = ToProcess.size() - 1;
    bool KeepGoing = true;
    
    bool FinishedOK = true;
    
    do {
        
        if(ToProcess[WorkIndex] == NumDigits - 1)
        {
            ToProcess[WorkIndex] = 0;
            if(WorkIndex == 0)
            {
                KeepGoing = false;
                FinishedOK = false;
            }
            else
            {
                WorkIndex--;
            }
        }
        else
        {
            ToProcess[WorkIndex]++;
            KeepGoing = false;
        }
        
    } while(KeepGoing);
    return FinishedOK;
}

void ShredIntoVec(const uint64_t ToShred, std::vector<std::size_t>& ToFill)
{
    uint64_t i = ToShred;
    if(i == 0)
    {
        ToFill.resize(1);
        ToFill[0]=0;
    }
    else
    {
        ToFill.resize(0);
        while(i > 0)
        {
            ToFill.push_back(i % 10);
            i /= 10;
        }
    }
}

void Apply(const std::vector<std::size_t>& Indices,
           const std::vector<std::size_t>& Elements,
           std::vector<std::size_t>& ToMutate)
{
    for(std::size_t i = 0; i < Indices.size(); i++)
    {
        ToMutate[Indices[i]] = Elements[i];
    }
}

void FillVec(const uint64_t n, std::vector<std::size_t>& ToFill)
{
    for(std::vector<std::size_t>::iterator i = ToFill.begin(); i != ToFill.end(); i++)
        *i = n;
}

bool Contains(uint64_t ToFind, const std::vector<std::size_t>& ToSearch)
{
    bool Answer = false;
    std::vector<std::size_t>::const_iterator i = ToSearch.begin();
    
    while( i != ToSearch.end() && Answer == false)
    {
        Answer = ToFind == *i;
        i++;
    }
    return Answer;
}

uint64_t PrimeSum(uint64_t BaseDigit, uint64_t ReplaceN)
{
    uint64_t Answer = 0;
    
    std::vector<std::size_t> TheValue, ReplaceVec, DigitsVec;
    TheValue.resize(NumDigits);
    ReplaceVec.resize(ReplaceN);
    
    uint64_t max = 10;
    
    for(int i = 2; i <= ReplaceN; i++) max *= 10;
    
    for(std::vector<std::size_t>::iterator i = TheValue.begin(); i != TheValue.end(); i++)
        *i = BaseDigit;
    
    for(std::size_t i = 0; i < ReplaceN; i++)
        ReplaceVec[i] = i;
    
    do {
        if(!IsIncreasing(ReplaceVec)) continue;
        for(uint64_t i = max / 10; i < max; i++)
        {
            FillVec(BaseDigit, TheValue);
            ShredIntoVec(i, DigitsVec);
            if(Contains(BaseDigit, DigitsVec)) continue;
            Apply(ReplaceVec, DigitsVec, TheValue);
            if(CheckVector(TheValue))
            {
                uint64_t t = 0;
                for(std::vector<std::size_t>::const_iterator i = TheValue.begin();
                    i != TheValue.end();
                    i++)
                {
                    t *= 10;
                    t += *i;
                }
                Answer += t;
            }
        }
    } while(GenerateNext(ReplaceVec));
    
    return Answer;
}

int main (int argc, char** argv)
{
    
    std::vector<uint64_t> Answers;
    
    Answers.resize(10);
    
    for(std::vector<uint64_t>::iterator i = Answers.begin(); i != Answers.end(); i++)
        *i = 0;
    
    for(int level = 1; level < NumDigits; level++)
    {
        for(uint64_t i = 0; i <= 9; i++)
        {
            if(Answers[i] == 0)
                Answers[i] = PrimeSum(i, level);
        }
    }
    
    std::cout << std::accumulate(Answers.begin(), Answers.end(), 0ul) << std::endl;
    
    return 0;
}