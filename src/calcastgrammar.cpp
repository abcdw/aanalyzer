#include <src/ast.cpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

using qi::_val;
using qi::_1;
using qi::_2;
using qi::_3;
using qi::_4;
using qi::double_;
using qi::grammar;
using qi::rule;
using qi::on_error;
using qi::fail;
using qi::space_type;
using phx::val;
using phx::construct;

template <typename Iterator>
struct calc_ast_grammar :
        grammar<Iterator, ast_node(), space_type>
{
    calc_ast_grammar() :
        calc_ast_grammar::base_type(expr)
    {

        id %= qi::lexeme[ qi::alpha];

        expr =
                term                [_val = _1]
            >> *( '+' > term        [_val = wrap_into_op_node(_val, _1, '+')]
                | '-' > term        [_val = wrap_into_op_node(_val, _1, '-')]
                )
        ;
        term =
                factor              [_val = _1]
            >> *( '*' > factor      [_val = wrap_into_op_node(_val, _1, '*')]
                | '/' > factor      [_val = wrap_into_op_node(_val, _1, '/')]
                )
        ;
                //(boost::phoenix::ref(vars_)[_1])
        factor =
                id                  [_val = _1]
                | double_           [_val = _1]
                | '(' > expr        [_val = _1] > ')'
                | '-' > factor      [_val = neg(_1)]
                | '+' > factor      [_val = _1]
        ;

        expr.name("expr");
        term.name("term");
        factor.name("factor");
        id.name("id");
        on_error<fail>(expr,
            std::cerr << val("Error! Expecting ") << _4 << " at: \""
                << construct<std::string>(_3, _2) << "\"\n\n");
    }
    rule<Iterator, ast_node(), space_type> expr, term, factor, id;
};
