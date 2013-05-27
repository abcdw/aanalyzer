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

ASNode::ASNode()
{
    id = qrand() % 1000;
}

ASNode::ASNode(double value_)
{
    key      = QString::number(value_);
    left     = NULL;
    right    = NULL;
    nodeType = leaf;
    id = qrand() % 1000;
}

ASNode::ASNode(ASNode* child_, char op_)
{
    key      = QString(op_);
    left     = child_;
    right    = NULL;
    nodeType = unaryOp;
    id = qrand() % 1000;
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
        else {
            *stream_ << "\t\t" << "n" << node_->getNodeId() << "leftNull" << "[style=\"filled\",label=\"NULL\"];" << endl;
            *stream_ << "\t\tn" << node_->getNodeId() << "--" << "n" << node_->getNodeId() << "leftNull" << endl;
        }

        if (node_->right != NULL) {
            *stream_ << "\t\tn" << node_->getNodeId() << "--" << "n" << node_->right->getNodeId() << ";" << endl;
            graphWalk(node_->right, stream_);
        } else {
            *stream_ << "\t\t" << "n" << node_->getNodeId() << "rightNull" << "[style=\"filled\",label=\"NULL\"];" << endl;
            *stream_ << "\t\tn" << node_->getNodeId() << "--" << "n" << node_->getNodeId() << "rightNull" << endl;
        }
    }
}
