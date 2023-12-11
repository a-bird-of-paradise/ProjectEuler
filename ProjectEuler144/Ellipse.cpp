#include "Ellipse.hpp"
#include "QuadSolve.hpp"
#include <cmath>

Ellipse::Ellipse(const long double A, const long double B) : a(A), b(B)
{}

long double Ellipse::GetA() const { return this->a; }
long double Ellipse::GetB() const { return this->b; }

void Ellipse::SetA(const long double A) { this->a = std::abs(A); }
void Ellipse::SetB(const long double B) { this->b = std::abs(B); }

std::vector<PT::Point2D> Ellipse::IntersectLine(const long double m, const long double c)
{
    long double A, B, C;
    
    A = a*a*m*m+b*b;
    B = 2*c*m*a*a;
    C = a*a*(c*c-b*b);
    
    std::vector<long double> xAnswers = QuadSolve(A, B, C);
    
    std::vector<PT::Point2D> Answers;
    PT::Point2D temp;
    
    if(xAnswers.size() >= 2)
    {
        temp.SetBasis(PT::System::Cartesian);
        temp.SetX(xAnswers[0]);
        temp.SetY(m*xAnswers[0]+c);
        Answers.push_back(temp);
        
        temp.SetBasis(PT::System::Cartesian);
        temp.SetX(xAnswers[1]);
        temp.SetY(m*xAnswers[1]+c);
        Answers.push_back(temp);
    }
    if(xAnswers.size() == 1)
    {
        temp.SetBasis(PT::System::Cartesian);
        temp.SetX(xAnswers[0]);
        temp.SetY(m*xAnswers[0]+c);
        Answers.push_back(temp);        
    }
    
    return Answers;
}

