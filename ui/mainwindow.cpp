/* This file is part of aanalyzer.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include "mainwindow.h"
#include <QtGui>
#include <src/astvisitor.cpp>
#include <QBoxLayout>
#include <QLineEdit>
#include <QWidget>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QBoxLayout *mainLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QLineEdit *inputLine = new QLineEdit("1.2 + (3.7 + 0.4) * 3.75");
    QPushButton *exitButton = new QPushButton("exit");
    QWidget *mainWidget = new QWidget();

    typedef std::string     str_t;
    typedef str_t::iterator str_t_it;

    str_t expression("1.2 + (3.7 + 0.4) * 3.75");
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


    mainLayout->setSpacing(0);
    mainLayout->addWidget(inputLine);

    mainLayout->addWidget(exitButton);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
}

MainWindow::~MainWindow()
{

}
