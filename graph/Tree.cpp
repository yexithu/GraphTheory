#include "Tree.h"
using namespace std;

TreeNode::TreeNode()
{
}

TreeNode::~TreeNode()
{
}

void TreeNode::printTree(TreeNode *node)
{
    cout << node->mIndex << " Children Size" << node->mChildren.size() <<
        " Weight Size " << node->mWeight.size() << endl;
}