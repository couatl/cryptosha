#include "graph_scene.h"
#include "graph_element.h"
#include <QGraphicsLinearLayout>

Graph_Scene::Graph_Scene(QGraphicsScene *parent) : QGraphicsScene(parent)
{
     //connect(ui->buttonBox, &QAction::triggered, scene, &Graph_Scene::on_ok_button_clicked);
    // QGraphicsLinearLayout * lay = new QGraphicsLinearLayout();
}

void Graph_Scene::on_ok_button_clicked()
{
    Graph_Element * element = new Graph_Element(1, 1);
    addItem(element);

}
