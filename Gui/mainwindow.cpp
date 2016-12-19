#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene_dialog.h"

#include <QDebug>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QListView>
#include <QLine>
#include <QGraphicsLineItem>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::MainWindow),
	cobra(string_t("report.txt"),
		  string_t("in.txt"),
		  string_t("out.txt"))
{
	ui->setupUi(this);

	ui->txtCodeEdit->setText(QString(
"for(q = 1; q; q = 0){ \n \
\n \
	@text.in = 43106\n \
	@key.in = 53399\n \
\n \
	for (i = 0; i < 8; i = 1 + i){\n \
		add(sbox, @SBOX[i], 4, 4, h<c 5 6 b 9 0 a d 3 e f 8 4 7 1 2>, <200*i, 50> , < 160,40 >)\n \
	}\n \
\n \
	for(s = 0; s < 4; s = 1 + s )\n \
	{\n \
		for(p = 0; p < 4; p = 1 + p )\n \
		{\n \
			connect(@text, <4*s + p>, @SBOX[s], <p>)\n \
			connect(@key, <4*s + p>, @SBOX[4 + s], <p>)\n \
		}\n \
	}\n \
\n \
	add(xor , @XOR, 16, 8, <42 ,142>, <300,50>)\n \
	add(nand, @NAND, 16, 8, <442,142>, <300,50>)\n \
\n \
	for(s = 0; s < 2; s = 1 + s )\n \
	{   \n \
		for(p = 0; p < 4; p = 1 + p )\n \
		{\n \
			connect(@SBOX[s], <p>, @XOR, <4*s + p>)\n \
			connect(@SBOX[s + 4], <p>, @XOR, <8 + 4*s + p>)\n \
			connect(@SBOX[s + 2], <p>, @NAND, <4*s + p>)\n \
			connect(@SBOX[s + 6], <p>, @NAND, <8 + 4*s + p>)\n \
		}\n \
	}\n \
\n \
	add( pblock, @PBLOCK, 16, 16, h<c 5 6 b 9 0 a d 3 e f 8 4 7 1 2>, <200, 100> , < 300,60 >)\n \
\n \
	for (i = 0; i < 8; i = i + 1)\n \
	{   \n \
		connect(@XOR, <i>,@PBLOCK, <i>)\n \
		connect(@NAND, <i>,@PBLOCK, <8 + i>)\n \
		connect(@PBLOCK, <i,8+i>,@cipher, <i , 8+i>)\n \
	}\n \
\n \
	assembly\n \
	run\n \
\n \
	cipher = @cipher.out\n \
}" ));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw()
{
}


void MainWindow::on_add_button_clicked()
{
}

void MainWindow::on_pushButton_clicked()
{

}



void MainWindow::on_btnRunCode_clicked()
{
	std::ofstream script_to_save(cry::gui::script_name);
	script_to_save << ui->txtCodeEdit->toPlainText().toStdString();
	script_to_save.close();


	cobra.set_new_input(cry::gui::script_name);

	auto reports = cobra.read().do_code();

	for (auto rep : reports)
	{
		ui->txtReportEdit->append( QString(rep.c_str()) );
	}

	std::ofstream info("scheme_info.txt");

	cobra.get_scheme()->push_to(info);

	info.close();

}


void MainWindow::on_btnDraw_clicked()
{
	SceneDialog * dialog = new SceneDialog(cobra.get_scheme());
	dialog->show();
}
