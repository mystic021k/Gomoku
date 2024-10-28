#pragma once
#include <QPoint>
#include <QMouseEvent>
#include <QGraphicsView>

class QGomokuView :
    public QGraphicsView
{
    Q_OBJECT
signals:
    void set_piece(QPoint* pos);
public:
    QGomokuView(QWidget* parent);
    QGomokuView(QGraphicsScene* scene, QWidget* parent);
    void mousePressEvent(QMouseEvent* event);
};

