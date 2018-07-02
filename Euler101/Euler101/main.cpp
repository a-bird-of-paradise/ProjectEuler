//
//  main.cpp
//  Euler101
//
//  Created by Mark Douglas on 03/11/2015.
//  Copyright © 2015 Mark Douglas. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>

typedef std::pair<int64_t,int64_t> POINT;

long double PolyFit(const std::vector<POINT>& Data, long double x)
{
    long double Answer = 0;
    
    for(int i =0; i < Data.size(); i++)
    {
        long double Temp = 1;
        for(int j = 0; j < Data.size(); j++)
        {
            if(i!=j)
            {
                Temp *= (x-Data[j].first);
                Temp /= (Data[i].first - Data[j].first);
            }
        }
        Temp *= Data[i].second;
        Answer += Temp;
    }
    return Answer;
}

long double BOP(const std::vector<POINT>& Data)
{
    return PolyFit(Data, Data.size()+1);
}

int main(int argc, const char * argv[]) {

    // test
    
    std::vector<int64_t> u { 1, 8, 27 };
    
    // real
    
    u.clear();
    for(int n = 1; n <= 10; n++)
    {
        int64_t ans = 0;
        for(int j = 0; j <= 10; j++)
        {
            ans += std::pow(n,j) * std::pow(-1,j);
        }
        u.push_back(ans);
    }
    
    std::vector<POINT> Data;
    
    long double Accum = 0;
    
    for(int i = 0; i < u.size(); i++)
    {
        Data.push_back(std::make_pair(i+1,u[i]));
        Accum += BOP(Data);
        
    }
    std::cout.precision(12);
    std::cout<<Accum<<std::endl;
    
    return 0;
}
