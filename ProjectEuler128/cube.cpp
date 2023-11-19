#include "cube.hpp"
#include <assert.h>
#include <algorithm>
#include <iterator>

cube::cube(long q, long r, long s) : q(q), r(r), s(s) 
{ 
    assert(q+r+s == 0); 
}

cube cube::operator+(const cube &b)
{
    return cube(q + b.q, r + b.r, s + b.s);
}

cube cube::operator-(const cube &b)
{
    return cube(q - b.q, r - b.r, s - b.s);
}

cube cube::operator*(const std::size_t &b)
{
    return cube(q*b, r*b, s*b);
}

const cube& cube::direction(const std::size_t i) const
{
    assert(i<6);
    return directions[i];
}

cube cube::neighbour(const std::size_t i) const
{
    return cube(*this) + direction(i);
}

cube cube::directions[6] = {
    cube(1,0,-1),
    cube(1,-1,0),
    cube(0,-1,1),
    cube(-1,0,1),
    cube(-1,1,0),
    cube(0,1,-1)
};

std::ostream& operator<<(std::ostream& os, const cube &c)
{
    os << '(' << c.q << ',' << c.r << ',' << c.s << ')';
    return os;
}

std::vector<cube> cube_ring(cube center, std::size_t radius)
{
    assert(radius != 0);
    std::vector<cube> answer;

    cube hex, direction;
    direction = hex.direction(4);
    hex = center;
    hex = center + direction * radius;

    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < radius; j++) {
            answer.push_back(hex);
            hex = hex.neighbour(i);
        }
    }
    return answer;
}

std::vector<cube> cube_spiral(cube center, std::size_t radius)
{
    std::vector<cube> answer, ring;

    answer.push_back(center);

    for(int i = 1; i <= radius; i++)
    {
        ring = cube_ring(center, i);
        std::move(ring.begin(), ring.end(), std::back_inserter(answer));
    }

    return answer;
}