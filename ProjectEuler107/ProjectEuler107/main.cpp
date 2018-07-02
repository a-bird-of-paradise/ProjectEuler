#include <iostream>
#include "UndirectedGraph.hpp"
#include <vector>
#include <fstream>
#include <sstream>

long long Saving(const UndirectedGraph& x)
{
    long long OrigSize = x.GraphWeight();
    
    UndirectedGraph MSG = x.MinimumSpanningGraph();
    
    long long NewSize = MSG.GraphWeight();
    
    std::cout << NewSize << ',' << OrigSize << std::endl;
    
    return (OrigSize - NewSize);
}

int main(int argc, const char** argv)
{
    UndirectedGraph x, y;
    
    Vertex A("A"), B("B"), C("C"), D("D"), E("E"), F("F"), G("G");
    
    x.AddVertex(A);
    x.AddVertex(B);
    x.AddVertex(C);
    x.AddVertex(D);
    x.AddVertex(E);
    x.AddVertex(F);
    x.AddVertex(G);
    
    x.AddEdge(A,B,16);
    x.AddEdge(A,C,12);
    x.AddEdge(A,D,21);
    
    x.AddEdge(B,D,17);
    x.AddEdge(B,E,20);
    
    x.AddEdge(C, D, 28);
    x.AddEdge(C, F, 31);
    
    x.AddEdge(D, E, 18);
    x.AddEdge(D, F, 19);
    x.AddEdge(D, G, 23);
    
    x.AddEdge(E, G, 11);
    
    x.AddEdge(F, G, 27);
    
    std::vector<Vertex> FileNodes;
    
    for(int i = 0; i < 40; i++)
    {
        Vertex v(std::to_string(i));
        FileNodes.push_back(v);
        y.AddVertex(v);
    }
    
    std::ifstream data("p107_network.txt");
    std::string Line, Item;
    int Row, Column;
    Row = 0;
    while(std::getline(data,Line))
    {
        Column = 0;
        std::istringstream iss(Line);
        while(std::getline(iss,Item,','))
        {
            if(Item == "-") Item = std::string("0");
            if(Column > Row && Item != "0")
                y.AddEdge(FileNodes[Column], FileNodes[Row], std::stoi(Item));
            Column++;
        }
        Row++;
    }
    
    
    std::cout << Saving(x) << std::endl;
    std::cout << Saving(y) << std::endl;
}
