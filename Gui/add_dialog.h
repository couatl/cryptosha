#ifndef ADD_DIALOG_H
#define ADD_DIALOG_H

#include <QDialog>
#include "graph_scene.h"

namespace Ui {
class add_dialog;
}

class add_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit add_dialog(Graph_Scene * myscene, QWidget *parent = 0);
    ~add_dialog();

private slots:
    void on_buttonBox_accepted();

    void on_xor_clicked();

    void on_nor_clicked();

private:
    Ui::add_dialog *ui;
    Graph_Scene *scene;
};

#endif // ADD_DIALOG_H
