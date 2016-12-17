#include "lay.h"
#include <QDebug>


lay::lay(QGraphicsItem *parent) : QGraphicsItem(parent)
{

    /*setFlag(GraphicsItemFlag::ItemIsSelectable);
    Graph_Element * item = new Graph_Element(2, 1, this);
    item->g_x = pos().x() + 70;
    item->g_y = pos().y() + 75;
    qDebug() << item->g_x;
    listElements.push_back(item);*/

}

lay::lay(int _x, int _y, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    setPos(_x, _y);
    setFlag(GraphicsItemFlag::ItemIsSelectable);
    int dist = 0;
    for (int i = 0; i < 3; ++i)
    {
        /*Graph_Element * item = new Graph_Element(2, 1, this);
        item->g_x = pos().x() + 70 + dist;
        item->g_y = pos().y() + 75;
        item->SetPinsCoords();
        //qDebug() << item->g_x;
        listElements.push_back(item);
        dist+=300;*/
    }
}

void lay::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int x = 0;
    painter->setPen(QPen(Qt::white, 1));
    painter->setBrush(Qt::white);
    painter->drawRect(0 , 0, (500+150)*listElements.size(), 150);
    //qDebug() << pos();
    for(auto it = listElements.begin(); it != listElements.end(); it++)
    {
        (*it)->setPos(x + 70, 50);


        x += 300;
    }
}

QRectF lay::boundingRect() const
{
    int y = 0;
    int x = 0;
    return QRectF(x , y, (500+150)*listElements.size(), 150);
}
