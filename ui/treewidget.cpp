#include "treewidget.h"
#include <QGraphicsGridLayout>
#include <QPushButton>
#include <QDebug>

TreeWidget::TreeWidget(QWidget *parent) :
    QWidget(parent)
{
    _scene = new QGraphicsScene(this);
    _view = new QGraphicsView(_scene);
    _view->setRenderHints(QPainter::SmoothPixmapTransform);
}

void TreeWidget::hideTree()
{
    _view->hide();
}

void TreeWidget::showTree(QByteArray arr)
{
    _scene->clear();
    qDebug() << arr;
    QProcess* p = new QProcess();

    p->setProcessChannelMode(QProcess::MergedChannels);
    p->start("dot", QStringList() << "-Tpng");
    p->write(arr);

    QByteArray data;
    QPixmap pixmap = QPixmap();

    while(p->waitForReadyRead(100)){
        data.append(p->readAll());
    }

    pixmap.loadFromData(data);

    _scene->addPixmap(pixmap);
    _view->show();
}
