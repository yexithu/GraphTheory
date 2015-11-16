#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <vector>

class Graph;
class TreeNode
{
public:

    TreeNode();
    ~TreeNode();

    int mIndex;
    std::vector<TreeNode *> mChildren;
    std::vector<int> mWeight;
    friend class Graph;

    static void printTree(TreeNode *node);
};

typedef TreeNode * Tree;
#endif