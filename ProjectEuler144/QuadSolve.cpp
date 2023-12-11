#include "QuadSolve.hpp"
#include <cmath>

std::vector<long double> QuadSolve(const long double a, const long double b, const long double c)
{
    std::vector<long double> Answer;
    long double discrim = b*b-4*a*c;
    if(discrim > 0)
    {
        Answer.push_back((-b+std::sqrt(discrim))/(2*a));
        Answer.push_back((-b-std::sqrt(discrim))/(2*a));
    }
    if(discrim==0)
    {
        Answer.push_back(-b/(2*a));
    }
    return Answer;
}