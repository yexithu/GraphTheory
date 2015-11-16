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

    void shortestPath(int start, int end, std::vector<int> &path, int &weight);

    void saveAllShortestPath(std::string pathFileName);
private:
    std::vector<Node *> mNodes;
    std::map<int, int> mRankIndexMap;

    void nodeShortestPath(int start, std::vector<int> &lastNodeVec, std::vector<int> &minWeightVec);
    void saveNodeShortestPath(std::string pathFileName, int start);
};

#endif