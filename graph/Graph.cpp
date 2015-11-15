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

void Graph::debug()
{
    for (size_t i = 0; i < mNodes.size(); ++i)
    {
        Node* node = mNodes[i];
        cout << node->mRank << " " << node->mMovieID << " " <<
            node->mSuccessors.size() << " " << node->mWeights.size() << endl;
    }

    cout << this->mRankIndexMap.size();
}