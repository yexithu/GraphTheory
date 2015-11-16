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


    //最短路部分
    void shortestPath(int start, int end, std::vector<int> &path, int &weight);
    void saveAllShortestPath(std::string pathFileName);

    //中心度部分
    void betweennessCentrality(std::vector<int> &bCentrilities);
    void closenessCentrality(std::vector<int> &cCentrilities);
    void saveBetweennessCentrality(std::string outfileName);
    void saveClosenessCentrality(std::string outfileName);

private:
    std::vector<Node *> mNodes;
    std::map<int, int> mRankIndexMap;

    //最短路部分
    void nodeShortestPath(int start, std::vector<int> &lastNodeVec, std::vector<int> &minWeightVec);
    void saveNodeShortestPath(std::string pathFileName, int start);
};

#endif