#include "graph_scene.h"
#include "graph_element.h"
#include <QGraphicsLinearLayout>

GraphScene::GraphScene(QGraphicsScene *parent) : QGraphicsScene(parent)
{
     //connect(ui->buttonBox, &QAction::triggered, scene, &Graph_Scene::on_ok_button_clicked);
    // QGraphicsLinearLayout * lay = new QGraphicsLinearLayout();
}

void GraphScene::on_ok_button_clicked()
{
	GraphElement * element = new GraphElement(1, 1);
    addItem(element);
}
