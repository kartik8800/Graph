#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <queue>
using namespace std;
class Graph
{
    public:
        Graph(int nodes)
        {
            numOfNodes = nodes;
            adjacencyList = vector<vector<pair<int,long long>>>(nodes+1);
        }
        virtual void addEdge(int u, int v, long long weight) = 0;
        virtual bool isCyclic() = 0;
        vector<int> breadthFirstTraversal(int source);
        vector<int> depthFirstTraversal(int source);
        int getNumberOfNodes()
        {
            return numOfNodes;
        }
    protected:
        //number of nodes in the graph
        int numOfNodes;
        //adjacency list for the graph
        //adjList[i] represents direct neighbours of node i
        //adjList[i].first represents an edge from node i to
        //node adjList[i].first.
        //adjList[i].second represents weight of the edge.
        vector<vector<pair<int,long long>>> adjacencyList;
        void dfsHelper(int source, vector<int> &nodesDiscovered, vector<bool> &vis);

};

vector<int> Graph::breadthFirstTraversal(int source)
{
    vector<int> nodesDiscovered;
    queue<int> nodesToExplore;
    vector<bool> visited(numOfNodes+1, 0);

    nodesToExplore.push(source);
    visited[source] = true;

    while(!nodesToExplore.empty())
    {
       int explore = nodesToExplore.front();
       nodesToExplore.pop();
       nodesDiscovered.push_back(explore);

       for(pair<int,long long> neighbours : adjacencyList[explore])
       {
           int neighbour = neighbours.first;
           if(!visited[neighbour])
           {
               visited[neighbour] = 1;
               nodesToExplore.push(neighbour);
           }
       }
    }
    return nodesDiscovered;
}

void Graph::dfsHelper(int source,vector<int> &nodesDiscovered, vector<bool> &vis)
{
    vis[source] = 1;
    nodesDiscovered.push_back(source);

    for(pair<int,long long> neighbours : adjacencyList[source])
       {
           int neighbour = neighbours.first;
           if(!vis[neighbour])
           {
               dfsHelper(neighbour, nodesDiscovered, vis);
           }
       }
}

vector<int> Graph::depthFirstTraversal(int source)
{
      vector<int> nodesDiscovered;
      vector<bool> vis(numOfNodes + 1, 0);
      dfsHelper(source, nodesDiscovered, vis);
      return nodesDiscovered;
}

#endif // GRAPH_H
