#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

class Node;

class Graph
{
public:
    Graph();
    ~Graph();

    void readNodes(std::string nodeFileName);
    void readEdges(std::string edgeFileName);
    
    int size();
    void debug();

    void saveShortestPath(int start);
    void shortestPath(int start, int end, std::vector<int> &path, int &weight);
private:
    std::vector<Node *> mNodes;
    std::map<int, int> mRankIndexMap;
};

#endif