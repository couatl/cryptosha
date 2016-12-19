#ifndef GRAPH_SCENE_H
#define GRAPH_SCENE_H
#include <QGraphicsScene>

class GraphScene : public QGraphicsScene
{
     Q_OBJECT

public:
	GraphScene(QGraphicsScene * parent = 0);
    void on_ok_button_clicked();
    void mouseReleaseEvent();




};

#endif // GRAPH_SCENE_H
