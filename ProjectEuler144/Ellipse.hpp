#pragma once
#include "Point.h"
#include <vector>

class Ellipse
{
public:
    Ellipse(long double A = 0, long double B = 0);
    long double GetA() const;
    long double GetB() const;
    void SetA(const long double A);
    void SetB(const long double B);
    std::vector<PT::Point2D> IntersectLine(const long double m, const long double c);
private:
    long double a, b;
};