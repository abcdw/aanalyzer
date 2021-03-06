#include "calcwidget.h"
#include <src/astvisitor.cpp>
#include <src/varvaluegrammar.cpp>
#include <string>
#include <map>

typedef std::map<char, double> vmap;
typedef std::map<std::string, double> svmap;

CalcWidget::CalcWidget(QWidget *parent) :
    QWidget(parent)
{
    mainLayout      = new QGridLayout(this);
    inputLine       = new QLineEdit(this);
    outputLine      = new QLineEdit(this);
    exitButton      = new QPushButton("exit", this);
    showTreeButton  = new QPushButton("show", this);
    treeWidget      = new TreeWidget(this);
    varTextEdit     = new QTextEdit(this);

    outputLine->setReadOnly(true);

    mainLayout->addWidget(inputLine, 0, 0, 1, 2);
    mainLayout->addWidget(outputLine, 1, 0, 1, 2);
    mainLayout->addWidget(showTreeButton, 2, 0);
    mainLayout->addWidget(exitButton, 2, 1);
    mainLayout->addWidget(varTextEdit, 3, 0, 1, 2);
    setLayout(mainLayout);

    QSize p = this->size();
    p.setWidth(500);
    parent->resize(p);

    connect(exitButton, SIGNAL(clicked()), parent, SLOT(close()));
    connect(inputLine, SIGNAL(textChanged(QString)), this, SLOT(showAnswer()));
    connect(showTreeButton, SIGNAL(clicked()), this, SLOT(showTree()));
    varTextEdit->append("x = 3;");
    varTextEdit->append("y = 10;");
    inputLine->setText("1.2 + (3.7 + -0.4 * (10e2 - 3) ) * 3.75");
}

bool CalcWidget::calcAnswer(double &ans, QString &error)
{


    str_t expression(inputLine->text().toStdString());
    calc_ast_grammar<str_t_it> calc;
    str_t_it begin = expression.begin(), end = expression.end();
    ast_node ast;

    //var_value_grammar<str_t_it> vvgramm;

    vmap vars;
    str_t varsText((varTextEdit->toPlainText()).toStdString());
    svmap svars;
    /*bool varsSuccess = qi::phrase_parse(varsText.begin()
                                 , varsText.end()
                                 , vvgramm
                                 , qi::space
                                 , svars);
    */
    //std::cerr << svars["x"];
    vars['x'] = 3;
    vars['y'] = 10;

    bool success = qi::phrase_parse(begin, end, calc, qi::space, ast);
    double result = boost::apply_visitor(ast_calculator(&vars), ast);

    std::cerr << "\n---------------------\n";
    if (success && (begin == end)) {
        std::cerr << result << "\n";
        std::cerr << "Parsing succeeded\n";
        ans = result;
    }
    else {
        std::cerr << "Parsing failed\nstopped at: "\
                      << str_t(begin, end) << "\"\n";
        error = QString::fromStdString(str_t(begin, end));
    }
    std::cerr << "---------------------\n";

    return success && (begin == end);
}

void CalcWidget::showTree()
{

    str_t expression(inputLine->text().toStdString());
    calc_ast_grammar<str_t_it> calc;
    str_t_it begin = expression.begin(), end = expression.end();
    ast_node ast;

    bool success = qi::phrase_parse(begin, end, calc, qi::space, ast);

    QByteArray arr = QByteArray();
    QTextStream stream(&arr, QIODevice::ReadWrite);
    stream << "graph ""{" << endl;
    stream << "\tnode[fontsize=10,margin=0,width=\".4\", height=\".3\"];" << endl;
    stream << "\tsubgraph cluster17{" << endl;
    int nodeCount = 0;
    ASTree tree(new ASNode(boost::apply_visitor(ast_converter(&nodeCount), ast)));
    //std::cerr << (tree._root->left->getNode());
    tree.graphWalk(tree._root, &stream);
    stream << "\t}\n" << "}" << endl;
    stream.flush();
    //std::cerr << stream.string()->toStdString();
    if (success && (begin == end)) {
        treeWidget->showTree(arr);
        //showTreeButton->setText("close");
    }

}

void CalcWidget::showAnswer()
{
    double result;
    QString error;
    bool calcSuccess = calcAnswer(result, error);

    if (calcSuccess) {
        QString answer = QString::number(result);
        outputLine->setText(answer);
    }
    else {
        outputLine->setText("Error at: " + error);
    }
}
