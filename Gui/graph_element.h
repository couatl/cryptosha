#ifndef GRAPH_ELEMENT_H
#define GRAPH_ELEMENT_H
#include <QGraphicsItem>
#include <QGraphicsLayoutItem>
#include <QPainter>
#include <QVector>
#include "graph_pin.h"

class Graph_Element : public QGraphicsItem
{
public:
    Graph_Element(QGraphicsItem * parent = 0);
    Graph_Element(int input, int output, QGraphicsItem * parent = 0);
    Graph_Element(const Graph_Element &) = default;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //QPainterPath shape() const;

    void SetPinsCoords();


    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    QRectF boundingRect() const;

    // Inherited from QGraphicsLayoutItem
    /*void setGeometry(const QRectF &geom) Q_DECL_OVERRIDE;
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const Q_DECL_OVERRIDE;*/
    std::string _name;
    QVector<graph_pin *> vInPins;
    QVector<graph_pin *> vOutPins;
    int g_x;
    int g_y;
    int InputPins;
    int OutputPins;
    //Graph_Element & operator=(const Graph_Element & obj);
private:



    QString _type;
    int width = 150;
    int height = 50;

};

#endif // GRAPH_ELEMENT_H
