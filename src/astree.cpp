#include "astree.h"

QString ASNode::GetNode() const
{
    return key;
}

ASNode::ASNode()
{

}

ASNode::ASNode(double value_)
{
    key      = QString::number(value_);
    nodeType = leaf;
}

ASNode::ASNode(ASNode* child_, char op_)
{
    key      = QString(op_);
    left     = child_;
    nodeType = unaryOp;
}

ASNode::ASNode(ASNode* left_, ASNode* right_, char op_)
{
    key      = QString(op_);
    left     = left_;
    right    = right_;
    nodeType = binaryOp;
}

ASTree::ASTree(ASNode* root_)
{
    _root = root_;
}
