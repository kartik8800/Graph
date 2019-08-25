#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H

#include "Graph.h"


class DirectedGraph : public Graph
{
    public:
        DirectedGraph(int nodes) : Graph(nodes)
        {

        }

        virtual void addEdge(int u, int v, long long w = 1)
        {
            adjacencyList[u].push_back({v, w});
        }
};

#endif // DIRECTEDGRAPH_H
