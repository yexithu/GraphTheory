#include "Node.h"

Node::Node()
{
}

Node::~Node()
{
}

int Node::lengthTo(Node *n)
{
    int l = -1;
    for (size_t i = 0; i < mSuccessors.size(); ++i)
    {
        if(mSuccessors[i]->mRank == n->mRank)
            l = mWeights[i];
    }

    return l;
}

