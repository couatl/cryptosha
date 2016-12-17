#ifndef LAY_H
#define LAY_H

#include <QGraphicsItem>
#include <QWidget>
#include "graph_element.h"
#include <QList>
#include <QPainter>

class lay : public QGraphicsItem
{
public:

lay(QGraphicsItem * parent = 0);
lay(int x, int y, QGraphicsItem * parent = 0);

void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

QRectF boundingRect() const;

QVector<Graph_Element*> listElements;

int g_x;
int g_y;

};

#endif // LAY_H
