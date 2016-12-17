#ifndef GRAPH_SCENE_H
#define GRAPH_SCENE_H
#include <QGraphicsScene>

#include "../QtCryptosha/settings.h"

class Graph_Scene : public QGraphicsScene
{
     Q_OBJECT
public:
    Graph_Scene(QGraphicsScene * parent = 0);
    void on_ok_button_clicked();
    void mouseReleaseEvent();

};

#endif // GRAPH_SCENE_H
