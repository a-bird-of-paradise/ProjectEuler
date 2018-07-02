#include "Vertex.hpp"
#include <iostream>

Vertex::Vertex() : Name("") {}

Vertex::Vertex(const std::string& Tag) : Name(Tag.c_str()){}

Vertex::Vertex(const Vertex& Orig) : Name(Orig.Name.c_str()) {}

Vertex::Vertex(Vertex&& Orig)
{
    this->Name = Orig.Name;
}

Vertex& Vertex::operator=(Vertex RHS)
{
    std::swap(this->Name,RHS.Name);
    return *this;
}

Vertex::~Vertex() {}

std::string Vertex::GetTag() const
{
    return this->Name;
}

void Vertex::SetTag(const std::string& NewTag)
{
    this->Name = NewTag;
}

bool operator< (const Vertex& lhs, const Vertex& rhs)
{
    return lhs.Name < rhs.Name;
}

bool operator== (const Vertex& lhs, const Vertex& rhs)
{
    return lhs.Name == rhs.Name;
}