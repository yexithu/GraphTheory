#include <iostream>
#include <vector>
#include "Graph.h"

using namespace std;

int main()
{
    const string nodeFile = "./Data/Nodes.txt";
    const string edgeFile = "./Data/Edges.txt";

    Graph graph;
    graph.readNodes(nodeFile);
    graph.readEdges(edgeFile);
    graph.debug();

    vector<int> path;
    int weight;
    graph.shortestPath(0, 1, path, weight);
    //graph.debug();
}
