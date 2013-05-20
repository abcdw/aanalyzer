#include "calcwidget.h"
#include <src/astvisitor.cpp>

CalcWidget::CalcWidget(QWidget *parent) :
    QWidget(parent)
{
    mainLayout      = new QGridLayout(this);
    inputLine       = new QLineEdit("1.2 + (3.7 + 0.4) * 3.75", this);
    outputLine      = new QLineEdit(this);
    exitButton      = new QPushButton("exit", this);
    showTreeButton  = new QPushButton("show", this);

    outputLine->setReadOnly(true);

    mainLayout->addWidget(inputLine, 0, 0, 1, 4);
    mainLayout->addWidget(outputLine, 1, 0, 1, 2);
    mainLayout->addWidget(showTreeButton, 1, 2);
    mainLayout->addWidget(exitButton, 1, 3);
    setLayout(mainLayout);

    connect(exitButton, SIGNAL(clicked()), parent, SLOT(close()));
    connect(inputLine, SIGNAL(textChanged(QString)), this, SLOT(showAnswer()));
}

bool CalcWidget::calcAnswer(double &ans)
{
    typedef std::string     str_t;
    typedef str_t::iterator str_t_it;

    str_t expression(inputLine->text().toStdString());
    calc_ast_grammar<str_t_it> calc;
    str_t_it begin = expression.begin(), end = expression.end();
    ast_node ast;

    bool success = qi::phrase_parse(begin, end, calc, qi::space, ast);
    double result = boost::apply_visitor(ast_visitor(), ast);

    std::cerr << "\n---------------------\n";
    if(success && begin == end) {
        std::cerr << result << "\n";
        std::cerr << "Parsing succeeded\n";
    }
    else {
        std::cerr << "Parsing failed\nstopped at: "\
                      << str_t(begin, end) << "\"\n";
    }
    std::cerr << "---------------------\n";
    ans = result;
    return success && begin == end;
}

void CalcWidget::showAnswer()
{
    double result;
    bool calcSuccess = calcAnswer(result);

    if (calcSuccess) {
        QString answer = QString::number(result);
        outputLine->setText(answer);
    }
    else {
        outputLine->setText("Parsing error!");
    }
}
