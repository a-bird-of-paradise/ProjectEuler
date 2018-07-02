#include <iostream>
#include <vector>
#include <map>
#include <cmath>

typedef uint64_t INT;
typedef std::tuple<INT,INT,INT> Point;

INT f(const INT& x, const INT& y, const INT& z, const INT& n)
{
    return(2*(x*y + y*z + x*z) + 4*(x+y+z+n-2)*(n-1));
    
}

const INT BailOut = 20000;

int main(int argc, const char * argv[]) {

    std::vector<Point> SearchSpace;
    std::vector<INT> SolCounts;
    
    std::map<INT,INT> SolMap;
    
    INT x, n;
    
    INT target = 1000;
    
    for(INT i = 1; f(i,i,i,1) <= BailOut; i++){
        //std::cout << "#i:" << i << std::endl;
        for(INT j = i; f(i,i,j,1) <= BailOut; j++){
            for(INT k = j; f(i,j,k,1) <= BailOut; k++){
                n = 1;
                x = f(i,j,k,n);
                while(x<=BailOut)
                {
                    SolMap[x]++;
                    n++;
                    x=f(i,j,k,n);
                }
            }
        }
    }
    
    for(std::map<INT,INT>::const_iterator i = SolMap.begin();
        i != SolMap.end();
        ++i)
    {
        //std::cout << i->first << "|" << i->second << std::endl;
        if(i->second == target) SolCounts.push_back(i->first);
    }
    
    std::cout << *std::min(SolCounts.begin(),SolCounts.end()) << std::endl;
    
    
}
