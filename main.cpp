#include "ui/mainwindow.h"
#include "src/parser.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setGeometry(13, 13, 500, 100);
    w.show();

    Parser pp(0);
    return a.exec();
}
