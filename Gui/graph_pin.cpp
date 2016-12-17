#include "graph_pin.h"
#include <QDebug>

graph_pin::graph_pin(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
}

graph_pin::graph_pin(int val, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    value = val;
}

void graph_pin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setPen(QPen(Qt::black, 1));
    if(value)
    {
        painter->setBrush(Qt::black);
        painter->drawEllipse(0, -2, 4, 4);
    }
    else
    {
        painter->setBrush(Qt::white);
        painter->drawEllipse(0, -2, 4, 4);
    }
}

QRectF graph_pin::boundingRect() const
{
    return QRectF(0, -2, 4, 4);
}


void graph_pin::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    if(this->isSelected())
        //qDebug() << "lol1" ;
    update();

}
