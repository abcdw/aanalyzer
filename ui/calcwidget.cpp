#include "calcwidget.h"
#include <src/astvisitor.cpp>

CalcWidget::CalcWidget(QWidget *parent) :
    QWidget(parent)
{
    mainLayout      = new QGridLayout(this);
    inputLine       = new QLineEdit(this);
    outputLine      = new QLineEdit(this);
    exitButton      = new QPushButton("exit", this);
    showTreeButton  = new QPushButton("show", this);

    outputLine->setReadOnly(true);

    mainLayout->addWidget(inputLine, 0, 0, 1, 2);
    mainLayout->addWidget(outputLine, 1, 0, 1, 2);
    mainLayout->addWidget(showTreeButton, 2, 0);
    mainLayout->addWidget(exitButton, 2, 1);
    setLayout(mainLayout);

    QSize p = this->size();
    p.setWidth(500);
    parent->resize(p);

    connect(exitButton, SIGNAL(clicked()), parent, SLOT(close()));
    connect(inputLine, SIGNAL(textChanged(QString)), this, SLOT(showAnswer()));

    inputLine->setText("1.2 + (3.7 + -0.4 * (10e2 - 3) ) * 3.75");
}

bool CalcWidget::calcAnswer(double &ans, QString &error)
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
        ans = result;
    }
    else {
        std::cerr << "Parsing failed\nstopped at: "\
                      << str_t(begin, end) << "\"\n";
        error = QString::fromStdString(str_t(begin, end));
    }
    std::cerr << "---------------------\n";

    return success && begin == end;
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
