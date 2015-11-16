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

size_t Graph::size()
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



//最短路径部分
//-------------------------------------------------------------------------
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
        cout << "Saving Shortpath" << i << endl;
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


//中心度部分
//---------------------------------------------------------------
void Graph::betweennessCentrality(std::vector<int> &bCentrilities)
{
    vector<int> tempB(this->mNodes.size(), 0);

    //对每一个节点
    for (size_t i = 0; i < mNodes.size(); ++i)
    {
        int start = i;
        vector<int> lastNodeVec, minWeightVec;
        this->nodeShortestPath(start, lastNodeVec, minWeightVec);

        //遍历它发出的所有路
        for (size_t j = 0; j < this->mNodes.size(); ++j)
        {
            int end = j;
            vector<int> path;
            
            //起点终点一样
            if (start == end)
                continue;
            //没有路
            if (lastNodeVec[end] == -1)
                continue;

            int current = end;
            while (current != -1)
            {
                path.push_back(current);
                current = lastNodeVec[current];
            }
            std::reverse(path.begin(), path.end());

            //所有路中非结点对
            for (size_t k = 1; k < path.size() - 1; ++k)
            {
                ++tempB[path[k]];
            }
        }
    }

    bCentrilities = tempB;
}

void Graph::closenessCentrality(std::vector<int> &cCentrilities)
{
    vector<int> tempC(mNodes.size(), 0);

    for (size_t i = 0; i < mNodes.size(); ++i)
    {
        int start = i;
        vector<int> lastNodeVec, minWeightVec;
        this->nodeShortestPath(start, lastNodeVec, minWeightVec);

        for (size_t j = 0; j < minWeightVec.size(); ++j)
        {
            if (minWeightVec[j] != -1)
            {
                tempC[start] += minWeightVec[j];
            }
        }
    }

    cCentrilities = tempC;
}

void Graph::saveBetweennessCentrality(std::string outfileName)
{
    ofstream outfile;
    outfile.open(outfileName, ios::out);

    vector<int> bCentrality;
    this->betweennessCentrality(bCentrality);
    for (size_t i = 0; i < bCentrality.size(); ++i)
    {
        cout << "Saving Centrality" << i << endl;
        outfile << bCentrality[i] << endl;
    }
    outfile.close();
}

void Graph::saveClosenessCentrality(std::string outfileName)
{
    ofstream outfile;
    outfile.open(outfileName, ios::out);

    vector<int> cCentrality;
    this->closenessCentrality(cCentrality);
    for (size_t i = 0; i < cCentrality.size(); ++i)
    {
        cout << "Saving Centrality" << i << endl;
        outfile << cCentrality[i] << endl;
    }
    outfile.close();
}


//最小生成树部分
void Graph::MinSpanningTree(Tree &tree)
{
    //选取结点中心度最小的结点作为根节点
    size_t root;
    vector<int> cCrentralities;
    this->closenessCentrality(cCrentralities);

    int minCCentra = INT_MAX;
    for (size_t i = 0; i < size(); ++i)
    {
        if (cCrentralities[i] < minCCentra)
        {
            minCCentra = cCrentralities[i];
            root = i;
        }
    }


    //构建所有树结点
    vector<TreeNode *> treeNodes;
    for (size_t i = 0; i < size(); ++i)
    {
        TreeNode *t = new TreeNode;
        t->mIndex = i;
        treeNodes.push_back(t);
    }
        
    vector<bool> flag(size(), true);

    flag[root] = false;
    while (true)
    {
        //选取最小边
        int start;
        int end;
        int minWeight = INT_MAX;

        for (size_t i = 0; i < size(); ++i)
        {
            for (size_t j = 0; j < size(); ++j)
            {
                //Flag[i] 为false 已在最小树内
                //Flag[j] 为true 不在最小树内
                if (!flag[i] && flag[j])
                {
                    int temp = mNodes[i]->lengthTo(mNodes[j]);
                    if (temp < minWeight)
                    {
                        start = i;
                        end = j;
                        minWeight = temp;
                    }
                }
            }
        }

        if (minWeight == INT_MAX)
            break;

        //更新树
        flag[end] = false;
        treeNodes[start]->mChildren.push_back(treeNodes[end]);
        treeNodes[start]->mWeight.push_back(minWeight);
    }
    
    tree = treeNodes[root];
}

void Graph::MinSpanningTree(Graph & g)
{
    for (size_t i = 0; i < mNodes.size(); ++i)
    {
    }
}