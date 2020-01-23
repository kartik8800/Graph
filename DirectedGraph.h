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
        vector<vector<int>> getStronglyConnectedComponents();
    
    private:
        
         vector<int> getFinishTimes();
         void finishTimeHelper(int src, vector<int>& finishTimes, vector<bool>& visited);
         DirectedGraph getReversal();

};

vector<vector<int>> DirectedGraph :: getStronglyConnectedComponents()
{
            vector<vector<int>> stronglyConnectedComponents;
            vector<int> finishTimes = this -> getFinishTimes();
            DirectedGraph reversedGraph = this -> getReversal();

            vector<bool> visited(this -> getNumberOfNodes() + 1, 0);

            for(int i = finishTimes.size() - 1; i >= 0; i--)
            {
                vector<int> SCC;
                if(!visited[finishTimes[i]])
                {
                  reversedGraph.dfsHelper(finishTimes[i], SCC, visited);
                  stronglyConnectedComponents.push_back(SCC);
                }
            }

            return stronglyConnectedComponents;
}

vector<int> DirectedGraph :: getFinishTimes()
{
             vector<int> finishTimes;
             vector<bool> visited(this -> getNumberOfNodes() + 1, 0);

             for(int src = 1; src <= this -> getNumberOfNodes(); src++)
             {
                 if(!visited[src])
                 {
                     finishTimeHelper(src, finishTimes, visited);
                 }
             }

             return finishTimes;
}


void DirectedGraph :: finishTimeHelper(int src, vector<int>& finishTimes, vector<bool>& visited)
{
             visited[src] = 1;

             for(auto neighbour : this -> adjacencyList[src])
             {
                 if(!visited[neighbour.first])
                    finishTimeHelper(neighbour.first, finishTimes, visited);
             }

             finishTimes.push_back(src);
}

DirectedGraph DirectedGraph :: getReversal()
{
             DirectedGraph gT(this -> getNumberOfNodes());

             for(int node = 1; node <= this -> getNumberOfNodes(); node++)
             {
                 for(auto edge : adjacencyList[node])
                 {
                     gT.addEdge(edge.first, node);
                 }
             }

             return gT;
}

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
