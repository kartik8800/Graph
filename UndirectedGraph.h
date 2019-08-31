///author : kartik8800
#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include "Graph.h"


class UndirectedGraph : public Graph
{
    private:
        void detectCycle(int src, vector<int> &parent, vector<bool> &visited, bool &cycle);
    public:
        UndirectedGraph(int nodes) : Graph(nodes)
        {

        }

        virtual bool isCyclic();

        virtual void addEdge(int u, int v, long long w = 1)
        {
            adjacencyList[u].push_back({v, w});
            adjacencyList[v].push_back({u, w});
        }

};

bool UndirectedGraph::isCyclic()
{
    if(numOfNodes <= 1)
        return false;
    vector<int> parent(numOfNodes + 1);
    vector<bool> visited(numOfNodes + 1, 0);
    bool cycle = 0;
    parent[1] = 1;
    detectCycle(1, parent, visited, cycle);
    return cycle;
}

void UndirectedGraph::
    detectCycle(int source, vector<int> &parent, vector<bool> &visited, bool &cycle)
{
   if(cycle)
      return;
   visited[source] = 1;
   for(auto neighbours : adjacencyList[source])
   {
       int neighbour = neighbours.first;
       if(visited[neighbour] && parent[source] != neighbour)
       {
          cycle = 1;
          return;
       }
       else if(!visited[neighbour])
       {
           parent[neighbour] = source;
           detectCycle(neighbour, parent, visited, cycle);
       }
   }
}

#endif // UNDIRECTEDGRAPH_H
