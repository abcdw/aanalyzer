#include <src/calcastgrammar.cpp>
#include <QTextStream>
#include <src/astree.h>
#include <string>
#include <map>

typedef std::map<char, double> vmap;

struct ast_calculator:
        boost::static_visitor<double>
{
    ast_calculator(vmap *vars_)
    {
        vars = vars_;
    }

    double operator() (double val) const
    {
        return val;
    }

    double operator() (char c) const
    {
        return (double)(*vars)[c];
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
    vmap *vars;
};

struct ast_converter:
        boost::static_visitor<ASNode>
{
    ast_converter(int *nodeCount_)
    {
        nodeCount = nodeCount_;
    }

    ASNode operator() (char c) const
    {
        ASNode t(c);
        t.setNodeId((*nodeCount)++);
        return t;
    }

    ASNode operator() (double value_) const
    {

        ASNode t(value_);
        t.setNodeId((*nodeCount)++);
        return t;
    }

    ASNode operator() (binary_op const& node) const
    {
        ASNode* n1 = new ASNode(boost::apply_visitor(*this, node.left));
        ASNode* n2 = new ASNode(boost::apply_visitor(*this, node.right));
        ASNode tmp(n1, n2, node.op);
        tmp.setNodeId((*nodeCount)++);
        return tmp;
    }

    ASNode operator() (unary_op const & node) const
    {
        ASNode tmp(new ASNode(boost::apply_visitor(*this, node.subj)), node.op);

        return tmp;
    }
    int *nodeCount;
};
