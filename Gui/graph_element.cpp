#include "graph_element.h"
#include "graph_pin.h"
#include <QPainter>
#include <QDebug>
#include <QGradient>
#include <QGraphicsLinearLayout>


Graph_Element::Graph_Element(QGraphicsItem *parent)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
}

Graph_Element::Graph_Element(int input, int output, QGraphicsItem * parent) : QGraphicsItem(parent)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    InputPins = input;
    OutputPins = output;

    for (int  i = 0; i < InputPins; ++i)
    {
        graph_pin * pin = new graph_pin(this);
        //pin->value = i%2;
        pin->number = i+1;
        /*k += width/(InputPins + 1);
        pin->g_x = g_x+k;
        pin->g_y = g_y;*/
        vInPins.push_back(pin);

    }

    for (int  i = 0; i < OutputPins; ++i)
    {
        graph_pin * pin = new graph_pin(this);
        //pin->value = i%2;
        pin->number = i+1;
        /*k += width/(OutputPins + 1);
        pin->g_x = g_x+k;
        pin->g_y = g_y+height;*/
        vOutPins.push_back(pin);
    }

}



void Graph_Element::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{



    int k = 0;
    painter->setBrush(Qt::white);
    QColor color;
    color.setRgb(123,123,123);

    painter->setPen(QPen(color, 2));
    painter->drawRect(0, 0, width, height);

    for (auto i = vInPins.begin(); i != vInPins.end(); ++i)
    {
        k += width/(InputPins + 1);
        (*i)->setPos(k, 0);

        //qDebug() << (*i)->GetPoint();
    }
    k = 0;

    for (auto i = vOutPins.begin(); i != vOutPins.end(); ++i)
    {
        k += width/(OutputPins + 1);
        (*i)->setPos(k, height);
    }

}



void Graph_Element::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    if(this->isSelected())
        //qDebug() << "lol" ;
    update();

}

void Graph_Element::SetPinsCoords()
{
    int k = 0;
    for (auto i = vInPins.begin(); i != vInPins.end(); ++i)
    {
        k += width/(InputPins + 1);
        (*i)->g_x = g_x+k+2;
        (*i)->g_y = g_y-2;
    }
    k = 0;
    for (auto i = vOutPins.begin(); i != vOutPins.end(); ++i)
    {
        k += width/(OutputPins + 1);
        (*i)->g_x = g_x+k+2;
        (*i)->g_y = g_y+height+2;
    }
}



QRectF Graph_Element::boundingRect() const
{
    return QRectF(0, 0, width, height);
}

/*Graph_Element & Graph_Element::operator=(const Graph_Element &obj)
{
    _name = obj._name;
    vInPins = obj.vInPins;
    vOutPins = obj.vOutPins;
    g_x = obj.g_x;
    g_y = obj.g_y;
    InputPins = obj.InputPins;
    OutputPins = obj.OutputPins;
    return *this;
}*/


