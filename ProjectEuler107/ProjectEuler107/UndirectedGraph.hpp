#pragma once

#include "Vertex.hpp"
#include <map>
#include <set>

typedef std::pair<Vertex,int> DestPair;
typedef std::set<DestPair> DestSet;


class UndirectedGraph
{
public:
    UndirectedGraph();
    ~UndirectedGraph();
    void AddVertex(const Vertex& v);
    void AddEdge(const Vertex& v1, const Vertex& v2, const int EdgeWeight);
    void RemoveEdge(const Vertex& v1, const Vertex& v2, const int EdgeWeight);
    
    UndirectedGraph MinimumSpanningGraph() const;
    
    long long GraphWeight() const;
    
    bool IsConnected() const;
    
    friend std::ostream& operator<<(std::ostream& lhs, const UndirectedGraph& rhs);
    
    std::set<Vertex> Neighbours (const Vertex& x) const;
    
private:
    std::map<Vertex,DestSet> TheGraph;
};
