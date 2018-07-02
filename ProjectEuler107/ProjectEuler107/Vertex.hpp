#pragma once
#include <string>

class Vertex
{
public:
    Vertex();
    Vertex(const std::string& Tag);
    Vertex(const Vertex& Orig);
    Vertex(Vertex&& Orig);
    Vertex& operator=(Vertex RHS);
    virtual ~Vertex();
    std::string GetTag() const;
    void SetTag(const std::string& NewTag);

    friend bool operator< (const Vertex& lhs, const Vertex& rhs);
    friend bool operator==(const Vertex& lhs, const Vertex& rhs);
    
private:
    std::string Name;
};

bool operator<  (const Vertex& lhs, const Vertex& rhs);
inline bool operator>  (const Vertex& lhs, const Vertex& rhs) { return rhs < lhs; }
inline bool operator<= (const Vertex& lhs, const Vertex& rhs) { return !(lhs > rhs); }
inline bool operator>= (const Vertex& lhs, const Vertex& rhs) { return !(rhs > lhs); }

bool operator== (const Vertex& lhs, const Vertex& rhs);
inline bool operator!= (const Vertex& lhs, const Vertex& rhs) {return !(lhs==rhs);}