#include <src/calcastgrammar.cpp>
#include <QTextStream>

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

struct ast_printer:
        boost::static_visitor<int>
{

    ast_printer(QTextStream* stream_)
    {
        stream = stream_;
    }

    int operator() (double val) const
    {
        *stream << "\t\t" << "n" << val << "[label=\"" << val <<"\"];" << endl;
        return 0;
    }

    int operator() (binary_op const& node) const
    {
        *stream << "\t\t" << "n" << node.op << "[label=\"" << node.op <<"\"];" << endl;
        *stream << "\t\tn" << node.op << "--" << "n" << node.op << ";" << endl;
        boost::apply_visitor(*this, node.left);
        *stream << "\t\tn" << node.op << "--" << "n" << node.op << ";" << endl;

        boost::apply_visitor(*this, node.right);

        return 1;
    }

    int operator() (unary_op const & node) const
    {
        *stream << "\t\t" << "n" << node.op << "[label=\"" << node.op <<"\"];" << endl;
        boost::apply_visitor(*this, node.subj);

        return 2;
    }

public:
    QTextStream* stream;

};
