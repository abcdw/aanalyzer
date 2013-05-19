#include <src/calcastgrammar.cpp>

struct ast_visitor :
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
