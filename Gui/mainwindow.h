#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph_scene.h"
#include <QGraphicsItem>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void on_tableWidget_clicked(const QModelIndex &index);
    void draw();

private slots:
     void on_add_button_clicked();

     void on_pushButton_clicked();

     void on_run_clicked();





	 void on_btnRunCode_clicked();

private:
    Ui::MainWindow *ui;
    Graph_Scene *scene;

	cryptosha::interpretator anaconda;
};

#endif // MAINWINDOW_H
