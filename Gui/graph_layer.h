/*#ifndef GRAPHLAYER_H
#define GRAPHLAYER_H

#include "graph_element.h"
#include <QGraphicsWidget>
#include <QList>
#include <QPainter>

class GraphLayer : public QGraphicsItem
{
    Q_OBJECT


public:
    GraphLayer();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void SetPins(int, int);

    QRectF boundingRect() const;


private:
    QList<Graph_Element *> el_list;
};

#endif // GRAPHLAYER_H*/
