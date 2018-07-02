#include "Point.h"
#include <cmath>

PT::Point2D::Point2D(const long double X,
                     const long double Y,
                     const PT::System Basis) : x(X), y(Y), basis(Basis)
{
    if(basis == PT::System::Polar)
    {
        x = std::abs(x); // silently force r>=0
        y = PT::WrapAngle(y);
    }
}

long double PT::WrapAngle(const long double ToWrap)
{
    long double temp = 0;
    temp = std::floor(ToWrap / (2*PT::pi()));
    temp = 2*PT::pi()*temp;
    temp = ToWrap - temp;
    return temp;
}

std::ostream& operator<<(std::ostream& os, const PT::Point2D& ThePoint)
{
    if(ThePoint.GetBasis() == PT::System::Cartesian)
    {
        os << "[" << ThePoint.GetX() << "," << ThePoint.GetY() << "]";
    }
    else
    {
        os << "(" << ThePoint.GetX() << "," << ThePoint.GetY() << ")";
    }
    return os;
}

long double PT::Point2D::GetX() const { return this->x; }
long double PT::Point2D::GetY() const { return this->y; }
PT::System PT::Point2D::GetBasis() const { return this->basis; }

void PT::Point2D::SetX(const long double X)
{
    if(this->basis == PT::System::Cartesian)
    {
        this->x = X;
    }
    else
    {
        this->x = std::abs(X); // enforce nonnegative r
    }
}

void PT::Point2D::SetY(const long double Y)
{
    if(this->basis == PT::System::Cartesian)
    {
        this->y = Y;
    }
    else
    {
        this->y = PT::WrapAngle(Y);
    }
}

void PT::Point2D::SetBasis(const PT::System Basis)
{
    if(Basis != this->basis)
    {
        if(Basis == PT::System::Cartesian)
        // convert to cartesian...
        {
            long double NewX = x * std::cos(y);
            long double NewY = x * std::sin(y);
            x=NewX;
            y=NewY;
        }
        else
        {
            // convert to polar
            long double NewR = std::sqrt(x*x + y*y);
            long double NewTheta;
            if(x==0)
            {
                NewTheta = PT::pi()/2;
            }
            else
            {
                NewTheta = std::atan2(y, x);
                NewTheta = WrapAngle(NewTheta);
            }
            x = NewR;
            y = NewTheta;
        }
    }
    else
    {
        // bases already correct, nothing to do!
    }
}

PT::Point2D PT::Point2D::ToCartesian() const
{
    PT::Point2D Answer;
    if(this->basis == PT::System::Cartesian)
    {
        Answer.x = this->x;
        Answer.y = this->y;
        Answer.basis=this->basis;
    }
    else
    {
        Answer.x= x * std::cos(y);
        Answer.y= x * std::sin(y);
        Answer.basis = PT::System::Cartesian;
    }
    return Answer;
}

PT::Point2D PT::Point2D::ToPolar() const
{
    PT::Point2D Answer;
    if(this->basis == PT::System::Polar)
    {
        Answer.x = this->x;
        Answer.y = this->y;
        Answer.basis=this->basis;
    }
    else
    {
        Answer.x = std::sqrt(x*x + y*y);
        Answer.y = PT::WrapAngle(std::atan2(y,x));
        Answer.basis = PT::System::Polar;
    }
    return Answer;
}