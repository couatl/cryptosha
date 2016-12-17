#ifndef GRAPH_PIN_H
#define GRAPH_PIN_H
#include <QGraphicsItem>
#include <QGraphicsLayoutItem>
#include <QPainter>

class graph_pin : public QGraphicsItem
{
public:
    graph_pin(QGraphicsItem *parent = 0);

    graph_pin(int val, QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void SetCoords(int, int);

    void SetNumber(int);

    QPointF GetPoint()
    {
        return QPointF(g_x, g_y);
    }

    QRectF boundingRect() const;

    void graph_pin::mousePressEvent(QGraphicsSceneMouseEvent *event);

    bool value;
    int g_x;
    int g_y;
    int number;
};

#endif // GRAPH_PIN_H
