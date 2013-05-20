
#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/spirit/include/phoenix.hpp>
#include <boost/variant.hpp>
#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

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

struct wrap_into_operation_node_impl
{
    template <typename T>
    struct result;

    template <
            typename This
          , typename Arg1
          , typename Arg2
          , typename Arg3
    >
    struct result<This(Arg1, Arg2, Arg3)>
    {
        typedef ast_node type;
    };

    ast_node operator() (ast_node const& left
                       , ast_node const& right
                       , char op) const
    {
        return binary_op(left, right, op);
    }
};

boost::phoenix::function<wrap_into_operation_node_impl> const
    wrap_into_op_node = wrap_into_operation_node_impl();
