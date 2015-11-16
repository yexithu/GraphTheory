#include <iostream>
#include <vector>
#include "Graph.h"
#include "Tree.h"
using namespace std;

void buildGraph(Graph &graph);
void testShortestPath(Graph &graph);
void testCentralities(Graph &graph);
void testMST(Graph &graph);
int main()
{
    Graph graph;
    buildGraph(graph);
    //testShortestPath(graph);
    //testCentralities(graph);
    testMST(graph);
}

void buildGraph(Graph &graph)
{

    const string nodeFile = "./Data/Nodes.txt";
    const string edgeFile = "./Data/Edges.txt";
    graph.readNodes(nodeFile);
    graph.readEdges(edgeFile);

}

void testShortestPath(Graph &graph)
{
    const string pathFile = "./Data/Paths.txt";

    vector<int> path;
    int weight;
    graph.shortestPath(100, 2, path, weight);
    for (size_t i = 0; i < path.size(); ++i)
    {
    cout << path[i] << " ";
    }
    cout << endl;
    cout << "Weight " << weight << endl;

    graph.saveAllShortestPath(pathFile);
}

void testCentralities(Graph &graph)
{
    const string bCentralityFile = "./Data/BetweennessCentrality.txt";
    const string cCentralityFile = "./Data/ClosenessCentrality.txt";

    vector<int> bCentralities;
    vector<int> cCentralities;

    graph.betweennessCentrality(bCentralities);
    for (size_t i = 0; i < bCentralities.size(); ++i)
    {
        cout << bCentralities[i] << endl;
    }
    graph.saveBetweennessCentrality(bCentralityFile);

    graph.closenessCentrality(cCentralities);
    for (size_t i = 0; i < cCentralities.size(); ++i)
    {
        cout << cCentralities[i] << endl;
    }
    graph.saveClosenessCentrality(cCentralityFile);
}

void testMST(Graph &graph)
{
    Tree tree = NULL;
    graph.MinSpanningTree(tree);
    cout << int(tree) << endl;
    TreeNode::printTree(tree);
}