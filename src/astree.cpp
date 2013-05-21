#include "astree.h"

QString ASNode::getNodeKey() const
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

void ASTree::graphWalk(ASNode* node_, QTextStream* stream_)
{
    if (node_ != NULL) {
        *stream_ << "\t\t" << "n" << node_->getNodeKey() << "[label=\"" << node_->getNodeKey() <<"\"];" << endl;

        if (node_->left != NULL) {
            *stream_ << "\t\tn" << node_->getNodeKey() << "--" << "n" << node_->left->getNodeKey() << ";" << endl;
            graphWalk(node_->left, stream_);
        }
        else {
            *stream_ << "\t\t" << "n" << node_->getNodeKey() << "leftNull" << "[style=\"filled\",label=\"NULL\"];" << endl;
            *stream_ << "\t\tn" << node_->getNodeKey() << "--" << "n" << node_->getNodeKey() << "leftNull" << endl;
        }

        if (node_->right != NULL) {
            *stream_ << "\t\tn" << node_->getNodeKey() << "--" << "n" << node_->right->getNodeKey() << ";" << endl;
            graphWalk(node_->right, stream_);
        } else {
            *stream_ << "\t\t" << "n" << node_->getNodeKey() << "rightNull" << "[style=\"filled\",label=\"NULL\"];" << endl;
            *stream_ << "\t\tn" << node_->getNodeKey() << "--" << "n" << node_->getNodeKey() << "rightNull" << endl;
        }
    }
}
