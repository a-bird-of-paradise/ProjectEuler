#include <iostream>
#include <utility>
#include <cmath>
#include "Ellipse.hpp"

template<typename T>
T RadToDegree(const T& Rad)
{
    return Rad * 180 / PT::pi();
}

int main(int argc, char** argv)
{
    
    Ellipse Boundary(5L,10L);
    std::vector<PT::Point2D> AllHits;
    
    long double InitialM, InitialC, NextM, NextC;
    
    long double TangentAngle, IncidentAngle, IncidentAngleAbsolute, FirstPsi;
    long double beta;
    
    PT::Point2D HitPoint;
    
    InitialM = (-9.6L - 10.1L) / (1.4L - 0L);
    InitialC = 10.1L;
    
    std::vector<PT::Point2D> Hits = Boundary.IntersectLine(InitialM, InitialC);
    
    HitPoint = Hits[0];
    AllHits.push_back(HitPoint);
    
    IncidentAngleAbsolute = PT::WrapAngle(std::atan(InitialM));
    
    TangentAngle = PT::WrapAngle(std::atan(-4 * HitPoint.GetX()/HitPoint.GetY()));
    
    IncidentAngle = PT::WrapAngle(std::abs(IncidentAngleAbsolute-TangentAngle));
    if(IncidentAngle < PT::pi()/2)
    {
        // already acute
    }
    else if(IncidentAngle < PT::pi())
    {
        IncidentAngle = PT::pi() - IncidentAngle;
    }
    else if(IncidentAngle < 3 * PT::pi()/2)
    {
        IncidentAngle = IncidentAngle - PT::pi();
    }
    else
    {
        IncidentAngle = 2 * PT::pi() - IncidentAngle;
    }
    
    
    FirstPsi = Hits[0].ToPolar().GetY();
    
    // ok  so we have (\alpha_1, \psi_1, and \theta_1)
    // which are (IncidentAngle, FirstPsi, and TangentAngle)
    // can also define beta
    
    beta = PT::WrapAngle(PT::pi() + FirstPsi + IncidentAngle - TangentAngle);
    
    // which is the angle of the reflected ray relative to the x axis, thus the gradient is
    
    NextM = std::tan(beta);
    
    // now: (y-b) = m(x-a)
    // y-b = mx - ma
    // y = mx + b-ma
    // c = b-ma
    
    NextC = HitPoint.GetY() - NextM * HitPoint.GetX();
    
    std::cout << NextM << "|" << NextC << std::endl;
    
    Hits = Boundary.IntersectLine(NextM, NextC);
    std::cout << Hits.size() << std::endl;
    for(auto& i: Hits) std::cout << i << std::endl;
    
    return 0;
}