#include "add_dialog.h"
#include "ui_add_dialog.h"
#include "graph_scene.h"

add_dialog::add_dialog(Graph_Scene * myscene, QWidget *parent) :
    scene(myscene),
    QDialog(parent),
    ui(new Ui::add_dialog)
{
    ui->setupUi(this);

}

add_dialog::~add_dialog()
{
    delete ui;
}



void add_dialog::on_buttonBox_accepted()
{
    scene->on_ok_button_clicked();
    QString str = ui->name->text();
}

void add_dialog::on_xor_clicked()
{
    ui->test->setEnabled(false);
}

void add_dialog::on_nor_clicked()
{
    ui->test->setEnabled(true);
}
