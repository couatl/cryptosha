#include "graph_element.h"
#include "graph_pin.h"
#include <QPainter>
#include <QDebug>
#include <QGradient>
#include <QGraphicsLinearLayout>


GraphElement::GraphElement(QGraphicsItem *parent)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
}

GraphElement::GraphElement(int input, int output, QGraphicsItem * parent)
	: QGraphicsItem(parent)
{
	setFlag(QGraphicsItem::ItemIsSelectable);
    InputPins = input;
    OutputPins = output;

	width = 20 * input;

    for (int  i = 0; i < InputPins; ++i)
    {
		gpin_ptr pin = std::make_shared<GraphPin>(this);

		pin->number = i+1;

        vInPins.push_back(pin);

    }

    for (int  i = 0; i < OutputPins; ++i)
    {
		gpin_ptr pin = std::make_shared<GraphPin>(this);

		pin->number = i+1;

        vOutPins.push_back(pin);
    }

}



void GraphElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{



    int k = 0;
    painter->setBrush(Qt::white);
    QColor color;
    color.setRgb(123,123,123);

    painter->setPen(QPen(color, 2));
    painter->drawRect(0, 0, width, height);
	painter->drawText(7,20, name);

    for (auto i = vInPins.begin(); i != vInPins.end(); ++i)
    {
        k += width/(InputPins + 1);
        (*i)->setPos(k, 0);

    }

    k = 0;

    for (auto i = vOutPins.begin(); i != vOutPins.end(); ++i)
    {
        k += width/(OutputPins + 1);
        (*i)->setPos(k, height);
    }

}



void GraphElement::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);

}

void GraphElement::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
    emit coordChanged();
}

void GraphElement::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    g_x = mapToScene(event->pos()).x();
    g_y = mapToScene(event->pos()).y();
    this->setPos(mapToScene(event->pos()));
    SetPinsCoords();
    emit coordChanged();
}

void GraphElement::SetPinsCoords()
{
    int k = 0;
    for (auto i = vInPins.begin(); i != vInPins.end(); ++i)
    {
		k += width / (InputPins + 1);
		(*i)->g_x = g_x + k + 2;
		(*i)->g_y = g_y - 2;
    }
    k = 0;
    for (auto i = vOutPins.begin(); i != vOutPins.end(); ++i)
    {
		k += width / (OutputPins + 1);
		(*i)->g_x = g_x + k + 2;
		(*i)->g_y = g_y + height + 2;
    }
}



QRectF GraphElement::boundingRect() const
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


