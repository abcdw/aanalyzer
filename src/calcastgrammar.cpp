#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <src/ast.cpp>

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

using qi::_val;
using qi::_1;
using qi::_2;
using qi::_3;
using qi::_4;
using qi::uint_;
using qi::grammar;
using qi::rule;
using qi::on_error;
using qi::fail;
using qi::space_type;
using phx::val;
using phx::construct;

