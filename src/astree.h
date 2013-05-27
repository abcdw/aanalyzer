#ifndef ASTREE_H
#define ASTREE_H
#include <QString>
#include <QTextStream>

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
    ASNode(char c);
    void setNodeId(int id_);
    QString getNodeKey() const;
    int getNodeId() const;
    NodeType nodeType;
    ASNode *left;
    ASNode *right;
    QString key;
    int id;
};

class ASTree
{
public:
    ASTree(ASNode* root_);
    void graphWalk(ASNode *node_, QTextStream* stream_);
    ASNode* _root;

private:

};

#endif // ASTREE_H
