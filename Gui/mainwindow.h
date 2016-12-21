#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>

#include "graph_scene.h"
#include "../QtCryptosha/cryptosha.hpp"



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

	 void on_btnRunCode_clicked();

	 void on_btnDraw_clicked();


private:

	Ui::MainWindow *ui;

	cryptosha::anaconda::interpretator cobra;
};

#endif // MAINWINDOW_H
