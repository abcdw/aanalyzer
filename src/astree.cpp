#include "astree.h"
#include <iostream>

QString ASNode::getNodeKey() const
{
    return key;
}

int ASNode::getNodeId() const
{
    return id;
}

void ASNode::setNodeId(int id_)
{
    id = id_;
}

ASNode::ASNode()
{

}

ASNode::ASNode(char c)
{
    key      = QString(c);
    left     = NULL;
    right    = NULL;
    nodeType = leaf;
}

ASNode::ASNode(double value_)
{
    key      = QString::number(value_);
    left     = NULL;
    right    = NULL;
    nodeType = leaf;
}

ASNode::ASNode(ASNode* child_, char op_)
{
    key      = QString(op_);
    left     = child_;
    right    = NULL;
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

void ASTree::graphWalk(ASNode* node_, QTextStream* stream_)
{
    std::cerr << node_->getNodeKey().toStdString() << std::endl;
    if (node_ != NULL) {
        *stream_ << "\t\t" << "n" << node_->getNodeId() << "[label=\"" << node_->getNodeKey() <<"\"];" << endl;

        if (node_->left != NULL) {
            *stream_ << "\t\tn" << node_->getNodeId() << "--" << "n" << node_->left->getNodeId() << ";" << endl;
            graphWalk(node_->left, stream_);
        }

        if (node_->right != NULL) {
            *stream_ << "\t\tn" << node_->getNodeId() << "--" << "n" << node_->right->getNodeId() << ";" << endl;
            graphWalk(node_->right, stream_);
        }
    }
}
