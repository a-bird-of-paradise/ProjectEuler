#pragma once

#include<utility>
#include<iostream>

namespace PT
{

    enum System { Cartesian, Polar };

class Point2D
{
public:
    Point2D(const long double X = 0, const long double Y = 0, const System Basis = Cartesian);
    Point2D ToCartesian() const;
    Point2D ToPolar() const;
    // getters
    long double GetX() const;
    long double GetY() const;
    System GetBasis() const;
    // setters
    void SetX(const long double X);
    void SetY(const long double Y);
    void SetBasis(const System Basis);
    
private:
    System basis;
    long double x, y;
};
    
    constexpr long double pi() { return 3.141592653589793238462643383279502884L; }
    
    long double WrapAngle(const long double ToWrap);

}

std::ostream& operator<<(std::ostream& os, const PT::Point2D& obj);