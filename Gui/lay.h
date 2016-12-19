#ifndef LAY_H
#define LAY_H

#include <QGraphicsItem>
#include <QWidget>
#include "graph_element.h"
#include <QList>
#include <QPainter>

class Lay : public QGraphicsItem
{
public:

	Lay(QGraphicsItem * parent = 0);
	Lay(int x, int y, QGraphicsItem * parent = 0);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	QRectF boundingRect() const;

	QVector<GraphElement*> listElements;

	int g_x;
	int g_y;

};

#endif // LAY_H
