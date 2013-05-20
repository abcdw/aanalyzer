#ifndef CALCWIDGET_H
#define CALCWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QString>

class CalcWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CalcWidget(QWidget *parent = 0);

private:
    QGridLayout     *mainLayout;
    QLineEdit       *inputLine;
    QLineEdit       *outputLine;
    QPushButton     *exitButton;
    QPushButton     *showTreeButton;
    bool calcAnswer(double &ans, QString &error);
signals:
    
public slots:
    void showAnswer();
};

#endif // CALCWIDGET_H
