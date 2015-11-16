#include <iostream>
#include <vector>
#include "Graph.h"

using namespace std;

int main()
{
    const string nodeFile = "./Data/Nodes.txt";
    const string edgeFile = "./Data/Edges.txt";
    const string pathFile = "./Data/Paths.txt";
    Graph graph;
    graph.readNodes(nodeFile);
    graph.readEdges(edgeFile);

    vector<int> path;
    int weight;
    graph.shortestPath(100, 2, path, weight);
    //graph.debug();
    for (int i = 0; i < path.size(); ++i)
    {
        cout << path[i] << " ";
    }
    cout << endl;
    cout << "Weight " << weight << endl;

    graph.saveAllShortestPath(pathFile);
}
