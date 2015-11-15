#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
class Graph;

class Node
{
public:
    Node();
    ~Node();

    bool operator < (const Node & n)
    {
        return this->mRank < n.mRank;
    }
private:
    int mMovieID;
    int mRank;
    
    //int 为对应的边权长度
    std::vector<Node *> mSuccessors;
    std::vector<int > mWeights;

    friend class Graph;
};
#endif