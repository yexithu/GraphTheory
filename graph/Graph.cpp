#include "Graph.h"
#include <fstream>
#include "Node.h"

using namespace std;

Graph::Graph()
{
}

Graph::~Graph()
{
}

void Graph::readNodes(std::string nodeFileName)
{
    fstream infile;
    infile.open(nodeFileName, ios::in);

    int index = 0;
    while (!infile.eof())
    {
        Node* node = new Node;
        infile >> node->mRank;
        infile >> node->mMovieID;
        
        this->mNodes.push_back(node);
        this->mRankIndexMap.insert(pair<int, int>(node->mRank, index));
        ++index;
    }

    infile.close();
}

void Graph::readEdges(std::string edgeFileName)
{
    fstream infile;
    infile.open(edgeFileName, ios::in);

    while (!infile.eof())
    {
        int start, end, weight;
        infile >> start >> end >> weight;

        Node *startN, *endN;
        startN = this->mNodes[this->mRankIndexMap[start]];
        endN = this->mNodes[this->mRankIndexMap[end]];

        startN->mSuccessors.push_back(endN);
        startN->mWeights.push_back(weight);
        endN->mSuccessors.push_back(startN);
        endN->mWeights.push_back(weight);
    }

    infile.close();
}

int Graph::size()
{
    return this->mNodes.size();
}

void Graph::debug()
{
    for (size_t i = 0; i < mNodes.size(); ++i)
    {
        Node* node = mNodes[i];
        cout << node->mRank << " " << node->mMovieID << " " <<
            node->mSuccessors.size() << " " << node->mWeights.size() << endl;
    }

    cout << this->mRankIndexMap.size() << endl;
}


void Graph::shortestPath(int start, int end, vector<int> &path, int &weight)
{
    vector<int> lastNodeVec, minWeightVec;
    this->nodeShortestPath(start, lastNodeVec, minWeightVec);
    
    if (start == end)
    {
        weight = 0;
        path.push_back(end);
        path.push_back(start);
        return;
    }


    if (lastNodeVec[end] == -1)
    {
        weight = -1;
        return;
    }

    int current = end;
    while (current != -1)
    {
        path.push_back(current);
        current = lastNodeVec[current];
    }
    weight = minWeightVec[end];
    std::reverse(path.begin(), path.end());
}

void Graph::nodeShortestPath(int start, vector<int> &lastNodeVec, vector<int> &minWeightVec)
{
    //以Rank为索引
    //与mNodes相对应
    vector<int> lastNode(size(), -1);

    //与mNodes相对应
    vector<int> minWeight(size(), -1);

    vector<bool> flag(size(), true);

    int current = start;
    minWeight[start] = 0;
    flag[start] = false;

    while (true)
    {
        Node *currentNode = mNodes[current];
        //update Weight
        bool isOver = true;

        for (size_t i = 0; i < mNodes.size(); ++i)
        {
            //在补集中，未确定最小值
            if (flag[i])
            {
                int tempLength = currentNode->lengthTo(mNodes[i]);
                //有直接连接
                if (tempLength != -1)
                {
                    isOver = false;
                    //之前无连接
                    if (minWeight[i] == -1)
                    {
                        minWeight[i] = minWeight[current] + tempLength;
                        lastNode[i] = current;
                    }
                    else
                    {
                        if (minWeight[current] + tempLength < minWeight[i])
                        {
                            minWeight[i] = minWeight[current] + tempLength;
                            lastNode[i] = current;
                        }
                    }
                }
            }
        }

        if (isOver)
            break;

        int next = -1;
        int minW = INT_MAX;
        //Find nextMin
        for (size_t i = 0; i < mNodes.size(); ++i)
        {
            if (flag[i])
            {
                if (minWeight[i] != -1 && minWeight[i] < minW)
                {
                    minW = minWeight[i];
                    next = i;
                }
            }
        }

        current = next;
        //cout << "Next " << next << " Weight" << minWeight[next] << endl;
        flag[next] = false;
    }

    lastNodeVec = lastNode;
    minWeightVec = minWeight;
}


void Graph::saveAllShortestPath(string pathFileName)
{
    ofstream ofile;
    ofile.open(pathFileName, ios::out);
    ofile.close();

    for (size_t i = 0; i < this->mNodes.size(); ++i)
    {
        cout << "Saving " << i << endl;
        saveNodeShortestPath(pathFileName, i);
    }
}

void Graph::saveNodeShortestPath(string pathFileName, int start)
{
    ofstream ofile;
    ofile.open(pathFileName, ios::app | ios::out);

    vector<int> lastNodeVec, minWeightVec;
    this->nodeShortestPath(start, lastNodeVec, minWeightVec);

    for (size_t i = 0; i < this->mNodes.size(); ++i)
    {
        int end = i;

        ofile << start;
        ofile << " ";
        ofile << end;
        ofile << endl;

        
        vector<int> path;
        int weight;

        if (start == end)
        {
            weight = 0;
            ofile << weight;
            ofile << " ";

            ofile << start << " " << end << endl;
            continue;
        }

        if (lastNodeVec[end] == -1)
        {
            weight = -1;
            ofile << weight;
            ofile << endl;
            continue;
        }

        int current = end;
        while (current != -1)
        {
            path.push_back(current);
            current = lastNodeVec[current];
        }
        weight = minWeightVec[end];
        std::reverse(path.begin(), path.end());
        ofile << weight;
        for (size_t j = 0; j < path.size(); ++j)
        {
            ofile << " " << path[j];
        }
        ofile << endl;

    }

    ofile.close();
}