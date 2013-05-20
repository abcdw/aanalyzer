#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QProcess>

class TreeWidget : public QWidget
{
    Q_OBJECT
private:
    QGraphicsScene *_scene;
    QGraphicsView *_view;

public:
    explicit TreeWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    void showTree(QByteArray &arr);
    void hideTree();
};

#endif // TREEWIDGET_H
