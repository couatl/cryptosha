#ifndef SCENE_DIALOG_H
#define SCENE_DIALOG_H


#include <QDialog>
#include <QGraphicsItem>
#include <QDebug>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QListView>
#include <QLine>
#include <QGraphicsLineItem>

#include "graph_element.h"
#include "graph_scene.h"
#include "lay.h"

#include "../QtCryptosha/cryptosha.hpp"

namespace Ui {
	class Dialog;
}

class SceneDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SceneDialog(cry::scheme_ptr ptr, QWidget *parent = 0);

	void drawUnstruct();

	void draw();

	void connect1();

	~SceneDialog();

private slots:
	void on_draw_clicked();

	void on_structurize_clicked();

	void makeCon();

	void on_btnDrawStruct_clicked();

private:
	static const int x0{ 100 };
	static const int y0{ 100 };
	static const int inter_element_width = 30;
	static const int inter_layer_width = 160;


	cry::scheme_ptr scheme_ptr;

	std::map<cry::id_t, GraphElement*> elements;
	Ui::Dialog *ui;
	GraphScene             *scene;
	std::vector<QGraphicsLineItem *> lines;
};



#endif // SCENE_DIALOG_H
