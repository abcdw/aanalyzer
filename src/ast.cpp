#include <boost/variant.hpp>

struct binary_op;
struct unary_op;

typedef boost::variant<
    double,
    boost::recursive_wrapper<binary_op>,
    boost::recursive_wrapper<unary_op>
> ast_node;

struct binary_op
{
    binary_op(ast_node const& left_,
              ast_node const& right_,
              char op_) :
        left(left_),
        right(right_),
        op(op_)
    {
    }
    char op;
    ast_node left;
    ast_node right;
};

struct unary_op
{
    unary_op(ast_node const& subj_,
             char op_) :
        subj(subj_),
        op(op_)
    {
    }
    char op;
    ast_node subj;
};
