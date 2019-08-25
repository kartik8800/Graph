#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H

#include "Graph.h"


class UndirectedGraph : public Graph
{
    public:
        UndirectedGraph(int nodes) : Graph(nodes)
        {

        }

        virtual void addEdge(int u, int v, long long w = 1)
        {
            adjacencyList[u].push_back({v, w});
            adjacencyList[v].push_back({u, w});
        }
};

#endif // DIRECTEDGRAPH_H
