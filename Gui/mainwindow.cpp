#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "add_dialog.h"

#include <QDebug>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QListView>
#include <QLine>
#include <QGraphicsLineItem>

#include "graph_element.h"
#include "graph_layer.h"
#include "lay.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new Graph_Scene();
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0, 100, 2000, 2000);




    //window->setPos(100, 150);


    //window2->setPos(100, 400);




    /*scene->addLine(QLineF((*(window->listElements.begin()))->mapToScene((*(window->listElements.begin()))->vOutPins[0]->pos()).x() + 145,
                   (*(window->listElements.begin()))->mapToScene((*(window->listElements.begin()))->vOutPins[0]->pos()).y() + 125,
            (*(window2->listElements.begin()))->mapToScene((*(window->listElements.begin()))->vInPins[0]->pos()).x()  + 120 ,
            (*(window2->listElements.begin()))->mapToScene((*(window->listElements.begin()))->vInPins[0]->pos()).y() + 75 ));*/
    //scene->addLine(QLineF(275, 255 , 250, 455));
    /*scene->addLine(QLineF((*(window->listElements.begin()))->vOutPins[0]->mapToScene(0,0),
                       (*(window2->listElements.begin()))->vInPins[0]->mapToScene(0,0)));*/
    //qDebug() << window->listElements[0]->vInPins[0]->g_x;
    //scene->addLine(QLineF(220, 225 , 320, 475));


    //scene->addLine(QLineF(window->listElements[0]->vOutPins[0]->GetPoint(), window2->listElements[1]->vInPins[0]->GetPoint()));
    //scene->addLine(QLineF(window->listElements[1]->vOutPins[0]->GetPoint(), window2->listElements[0]->vInPins[1]->GetPoint()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw()
{
    int layers_num = 4;
    int elements_num = 4;
    int dist;
    std::vector<lay*> scheme;
    int x = 100;
    int y = 200;
    for (int i = 0; i < layers_num; ++i)
    {
        lay * layer = new lay(x, (i+1) * 200);
        dist = 0;
        for (int j = 0; j < elements_num; ++j)
        {
            Graph_Element * item = new Graph_Element(2, 2, layer);
            //item->_name = std::string(std::to_string(j));
            for (int  k = 0; k < item->InputPins; ++k)
            {
                item->vInPins[k]->value = k%2;
            }
            for (int  k = 0; k < item->OutputPins; ++k)
            {
                item->vOutPins[k]->value = k%2;
            }
            item->g_x = layer->pos().x() + 70 + dist;
            item->g_y = layer->pos().y() + 50;
            item->SetPinsCoords();
            //qDebug() << item->g_x;
            layer->listElements.push_back(item);
            dist+=300;
        }
        scheme.push_back(layer);
        scene->addItem(layer);
    }
    scheme[0]->listElements[0]->_name = "0";
    scheme[0]->listElements[1]->_name = "1";
    scheme[1]->listElements[0]->_name = "00";
    scheme[2]->listElements[1]->_name = "11";

    std::map< std::pair<std::string, std::string>, std::pair<int, int> > connections = { {{"1", "00"}, {1, 1}},
                                                                                         {{"1", "11"}, {0, 1}}
                                                                                       };
    for (auto it = connections.begin(); it != connections.end(); ++it)
    {
        QPointF p1;
        QPointF p2;
        int stop_flag = 0;
        bool val = false;
        for (int i = 0; i < layers_num; ++i)
        {
            for (int j = 0; j < elements_num; ++j)
            {
                if (scheme[i]->listElements[j]->_name == it->first.first)
                {
                    p1 = scheme[i]->listElements[j]->vOutPins[it->second.first]->GetPoint();
                    if (scheme[i]->listElements[j]->vOutPins[it->second.first]->value)
                        val = true;
                    stop_flag++;

                }
                if (scheme[i]->listElements[j]->_name == it->first.second)
                {
                    p2 = scheme[i]->listElements[j]->vInPins[it->second.second]->GetPoint();
                    stop_flag++;
                }
                if (stop_flag == 2)
                    break;


            }
            if (stop_flag == 2)
                break;
        }
        if (val)
            scene->addLine(QLineF(p1, p2), QPen(Qt::black, 2));
        else
            scene->addLine(QLineF(p1, p2), QPen(Qt::black, 1));



    }
    //scene->addLine(QLineF(p1, p2), QPen((Qt::black, 3)));
    //scheme[2]->listElements[1]->vOutPins[0].GetPoint()

}


void MainWindow::on_add_button_clicked()
{
    add_dialog * pointer = new add_dialog(scene, this);
    pointer->exec();
}

void MainWindow::on_pushButton_clicked()
{
	for(auto& it : scene->items())
    {

        if(it->isSelected())
        {
            scene->removeItem(it);
            scene->update();
            //scene->removeItem(it1);
        }

    }

}

void MainWindow::on_run_clicked()
{

}



void MainWindow::on_btnRunCode_clicked()
{
	std::ofstream script(cry::gui::script_name);

	script << ui->txtCodeEdit->toPlainText().toStdString();

	script.close();
}




