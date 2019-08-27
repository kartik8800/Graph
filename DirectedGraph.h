#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H
#include <stack>
#include "Graph.h"
using namespace std;

class DirectedGraph : public Graph
{
    public:
        DirectedGraph(int nodes) : Graph(nodes)
        {

        }

        virtual bool isCyclic();

        virtual void addEdge(int u, int v, long long w = 1)
        {
            adjacencyList[u].push_back({v, w});
        }

};

bool DirectedGraph::isCyclic()
{
    int numOfNodes = getNumberOfNodes();
    if(numOfNodes <= 1)
       return false;
    vector<bool> visited(numOfNodes + 1, 0);
    vector<bool> inPath(numOfNodes + 1, 0);
    stack<pair<int,int>> path;
    for(int i=1; i <= numOfNodes; i++)
    {
        if(visited[i])
            continue;
        path.push({i,0});
        visited[i] = 1;
        inPath[i] = 1;
        while(!path.empty())
        {
            int source = path.top().first;
            int idx = path.top().second;
            path.pop();
            if(idx == adjacencyList[source].size())
            {
                inPath[idx] = 0;
                continue;
            }
            else
            {
                int explore = adjacencyList[source][idx].first;
                if(inPath[explore])
                    return true;
                if(visited[explore])
                {
                    path.push({source, idx + 1});
                    continue;
                }
                inPath[explore] = visited[explore] = true;
                path.push({source, idx + 1});
                path.push({explore, 0});
            }
        }
    }
    return false;
}

#endif // DIRECTEDGRAPH_H
