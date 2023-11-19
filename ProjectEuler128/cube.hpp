#pragma once
#include <compare>
#include <vector>
#include <iostream>

class cube
{
public:
    cube(long q, long r, long s);
    cube() : q(0), r(0), s(0) {} 
    cube(const cube& other) = default;

    cube operator+(const cube &b);
    cube operator-(const cube &b);
    cube operator*(const std::size_t &b);
    cube& operator=(const cube& other) = default;

    auto operator<=>(const cube&) const = default;

    const cube& direction(const std::size_t i) const;
    cube neighbour(const std::size_t i) const;

    friend std::ostream& operator<< (std::ostream& stream, const cube& c);

    long q,r,s;
private:
    static cube directions[6];
};

std::vector<cube> cube_ring(cube center, std::size_t radius);
std::vector<cube> cube_spiral(cube center, std::size_t radius);