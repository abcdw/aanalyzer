#include <boost/variant.hpp>
#include <boost/phoenix.hpp>

struct binary_op;
struct unary_op;

typedef boost::variant<
    double
  , boost::recursive_wrapper<binary_op>
  , boost::recursive_wrapper<unary_op>
> ast_node;

struct binary_op
{
    binary_op(ast_node const& left_
            , ast_node const& right_
            , char op_) :
        left(left_)
      , right(right_)
      , op(op_)
    {
    }
    char op;
    ast_node left;
    ast_node right;
};

struct unary_op
{
    unary_op(ast_node const& subj_
           , char op_) :
        subj(subj_)
      , op(op_)
    {
    }
    char op;
    ast_node subj;
};

struct neg_impl
{
    template <typename T>
    struct result;

    template <
            typename This
          , typename Arg
    >
    struct result<This(Arg)>
    {
        typedef ast_node type;
    };

    ast_node operator() (ast_node const& node) const
    {
        return unary_op(node, '-');
    }
};

boost::phoenix::function<neg_impl> const neg = neg_impl();
