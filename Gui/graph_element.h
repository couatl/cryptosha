#ifndef GRAPH_ELEMENT_H
#define GRAPH_ELEMENT_H
#include <QGraphicsItem>
#include <QGraphicsLayoutItem>
#include <QPainter>
#include <QVector>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QObject>
#include <memory>

#include "graph_pin.h"

class GraphElement : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
	GraphElement(QGraphicsItem * parent = 0);
	GraphElement(int input, int output, QGraphicsItem * parent = 0);
	GraphElement(const GraphElement &) = default;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //QPainterPath shape() const;

    void SetPinsCoords();


    //void mousePressEvent(QGraphicsSceneMouseEvent *event);

    QRectF boundingRect() const;

    // Inherited from QGraphicsLayoutItem
    /*void setGeometry(const QRectF &geom) Q_DECL_OVERRIDE;
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const Q_DECL_OVERRIDE;*/

	cry::id_t id;

	using gpin_ptr = std::shared_ptr<GraphPin>;
	QVector<gpin_ptr> vInPins;
	QVector<gpin_ptr> vOutPins;
    int g_x;
    int g_y;
    int InputPins;
    int OutputPins;
    //Graph_Element & operator=(const Graph_Element & obj);

	int get_width() const
	{
		return width;
	}

signals:
    void coordChanged();

private:

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

public:
	QString type;
	QString name;

    int width = 150;
    int height = 50;


};

#endif // GRAPH_ELEMENT_H
