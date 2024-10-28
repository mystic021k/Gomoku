#include "qgomokuview.h"

QGomokuView::QGomokuView(QWidget* parent)
    : QGraphicsView(parent)
{
}

QGomokuView::QGomokuView(QGraphicsScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent)
{
}

void QGomokuView::mousePressEvent(QMouseEvent* event)
{
    QPoint point = event->pos();
    emit set_piece(&point);
}
