#include <boost/spirit/include/qi.hpp>
#include <string>
#include <map>

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;
/*
template <typename Iterator>
struct var_value_grammar
    : qi::grammar<
          Iterator
        , std::map<std::string, double>()
      >
{
    var_value_grammar()
        : var_value_grammar::base_type(pairs)
    {
        pairs = pair % ';' >> ';';
        pair  = key >> -('=' >> value);
        key   = (qi::alpha | qi::char_('_')) >> *(qi::alnum | qi::char_('_'));
        value = qi::double_;
    }

    qi::rule<
          Iterator
        , std::map<std::string, double>()
    > pairs;

    qi::rule<
          Iterator
        , std::pair<std::string, double>()
    > pair;

    qi::rule<Iterator, std::string()> key;
    qi::rule<Iterator, double> value;
};
*/
