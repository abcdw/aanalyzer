#include <src/calcastgrammar.cpp>
#include <QTextStream>
#include <src/astree.h>

struct ast_calculator:
        boost::static_visitor<double>
{
    double operator() (double val) const
    {
        return val;
    }

    double operator() (binary_op const& node) const
    {

        double left_value = boost::apply_visitor(*this, node.left);
        double right_value = boost::apply_visitor(*this, node.right);

        switch(node.op) {
        case '+':
            return left_value + right_value;
        case '-':
            return left_value - right_value;
        case '*':
            return left_value * right_value;
        case '/':
            return left_value / right_value;
        default:
            return 0;
        }
    }

    double operator() (unary_op const & node) const
    {
        double subj_val = boost::apply_visitor(*this, node.subj);

        switch(node.op) {
        case '-':
            return -subj_val;
        default:
            return 0;
        }
    }
};

struct ast_converter:
        boost::static_visitor<ASNode>
{

    ASNode operator() (double value_) const
    {
        return ASNode(value_);
    }

    ASNode operator() (binary_op const& node) const
    {
        ASNode* n1 = new ASNode(boost::apply_visitor(*this, node.left));
        ASNode* n2 = new ASNode(boost::apply_visitor(*this, node.right));
        ASNode tmp(n1, n2, node.op);

        return tmp;
    }

    ASNode operator() (unary_op const & node) const
    {
        ASNode tmp(new ASNode(boost::apply_visitor(*this, node.subj)), node.op);

        return tmp;
    }

};
