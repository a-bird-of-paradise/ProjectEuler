#include "UndirectedGraph.hpp"
#include <iostream>
#include <queue>

UndirectedGraph::UndirectedGraph(){}
UndirectedGraph::~UndirectedGraph(){}

void UndirectedGraph::AddVertex(const Vertex &v)
{
    TheGraph[v];
}

void UndirectedGraph::AddEdge(const Vertex &v1, const Vertex &v2, const int EdgeWeight)
{
    this->TheGraph.find(v1)->second.insert(std::make_pair(v2,EdgeWeight));
    this->TheGraph.find(v2)->second.insert(std::make_pair(v1,EdgeWeight));
}

void UndirectedGraph::RemoveEdge(const Vertex &v1, const Vertex &v2, const int EdgeWeight)
{
    // find the edge if it exists and remove it
    
    std::map<Vertex,DestSet>::iterator FoundIt;
    DestSet::iterator EdgeIt;
    
    FoundIt = this->TheGraph.find(v1);
    EdgeIt = FoundIt->second.find(std::make_pair(v2,EdgeWeight));
    FoundIt->second.erase(EdgeIt);
    
    FoundIt = this->TheGraph.find(v2);
    EdgeIt = FoundIt->second.find(std::make_pair(v1, EdgeWeight));
    FoundIt->second.erase(EdgeIt);
}

std::ostream& operator<<(std::ostream& lhs, const UndirectedGraph& rhs)
{
    
    for(auto&& i : rhs.TheGraph)
    {
        std::cout << i.first.GetTag() << std::endl;
        for(auto&& j : i.second)
        {
            std::cout << j.first.GetTag() << "," << j.second << "|";
        }
        std::cout << std::endl << "-----" << std::endl;
    }
    
    return lhs;
}


std::set<Vertex> UndirectedGraph::Neighbours (const Vertex& x) const
{
    std::set<Vertex> Answer;
    
    std::map<Vertex,DestSet>::const_iterator FoundIt = this->TheGraph.find(x);
    
    for(auto&& i : FoundIt->second) Answer.insert(i.first);
    
    return Answer;
}

bool UndirectedGraph::IsConnected() const
{
    std::queue<Vertex> ToVisit;
    std::set<Vertex> Visited, TheseNeighbours;
    
    std::map<Vertex,DestSet>::const_iterator CurrentNode;
    
    CurrentNode = this->TheGraph.begin();
    
    ToVisit.push(CurrentNode->first);
    Visited.insert(CurrentNode->first);
    
    while(ToVisit.size() > 0)
    {
        CurrentNode = this->TheGraph.find(ToVisit.front());
        ToVisit.pop();
        TheseNeighbours = this->Neighbours(CurrentNode->first);
        for(auto&& i : TheseNeighbours)
        {
            if(Visited.find(i) == Visited.end())
            {
                ToVisit.push(i);
                Visited.insert(i);
            }
        }
    }
    return Visited.size() == this->TheGraph.size();
}

long long UndirectedGraph::GraphWeight() const
{
    long long Answer = 0;
    for(auto&& i : this->TheGraph)
    {
        for(auto&& j : i.second)
        {
            Answer += j.second;
        }
    }
    return Answer/2;
}

UndirectedGraph UndirectedGraph::MinimumSpanningGraph() const
{
    UndirectedGraph Answer;
    Vertex Source, Dest;
    int ThisLength, MaxLength = 0;
    Answer.AddVertex(this->TheGraph.begin()->first);
    
    std::map<Vertex,DestSet>::const_iterator ThisOne;
    
    for(auto&& i : this->TheGraph)
        for(auto&& j : i.second)
            if(j.second > MaxLength)
                MaxLength = j.second;
    
    while(Answer.TheGraph.size() != this->TheGraph.size())
    {
        std::set<Vertex> InAnswer;
        for(auto&& i : Answer.TheGraph) InAnswer.insert(i.first);
        
        ThisLength=MaxLength;
        
        for(auto&& i : InAnswer)
        {
            ThisOne = this->TheGraph.find(i);
            for(auto&& j : ThisOne->second)
            {
                if(j.second <= ThisLength && InAnswer.find(j.first)==InAnswer.end())
                {
                    Source = i;
                    Dest = j.first;
                    ThisLength = j.second;
                }
            }
        }
        Answer.AddVertex(Dest);
        Answer.AddEdge(Source, Dest, ThisLength);
    }
    return Answer;
}