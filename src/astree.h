#ifndef ASTREE_H
#define ASTREE_H
#include <QString>

enum NodeType {
    leaf
  , unaryOp
  , binaryOp
};

struct ASNode{

    ASNode();
    ASNode(double value_);
    ASNode(ASNode* child_, char op_);
    ASNode(ASNode* left_, ASNode* right_, char op_);
    QString GetNode() const;
    NodeType nodeType;
    ASNode *left;
    ASNode *right;
    QString key;
};

class ASTree
{
public:
    ASTree(ASNode* root_);
private:
    ASNode* _root;
};

#endif // ASTREE_H
