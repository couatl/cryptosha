#include <memory>
#include "scene_dialog.h"
#include "ui_canvas_dialog.h"


SceneDialog::SceneDialog(cry::scheme_ptr ptr,QWidget *parent) :
	QDialog(parent),
	scheme_ptr(ptr),
	ui(new Ui::Dialog)
{
	ui->setupUi(this);
	scene = new GraphScene();
	ui->graphicsView->setScene(scene);
	// scene->setSceneRect(0, 100, 2000, 2000);
}


void SceneDialog::connect1()
{
	QPointF out_pin;
	QPointF in_pin;
	bool is_true;

	for (auto& wire : scheme_ptr->wires())
	{
		out_pin = elements[wire.first.id1]->vOutPins[wire.second.pin1]->GetPoint();
		 in_pin = elements[wire.first.id2]->vInPins[wire.second.pin2]->GetPoint();

		is_true = elements[wire.first.id1]->vOutPins[wire.second.pin1]->value;

		if (is_true){
			lines.push_back(scene->addLine(QLineF(out_pin,in_pin), QPen(Qt::red,1)));
		}
		else{
			lines.push_back(scene->addLine(QLineF(out_pin,in_pin), QPen(Qt::black,1)));
		}
	}

}



void SceneDialog::drawUnstruct()
{

	elements.clear();

	for (auto& layer : scheme_ptr->circuit())
	{

		for (auto id : layer)
		{

			auto g_info = scheme_ptr->graphic_information(id);
			auto ptr_element = scheme_ptr->element(id);

			auto graph_element = new GraphElement(g_info.iosize.in, g_info.iosize.out);
			//graph_element->setFlag(QGraphicsItem::ItemIsMovable);

			elements[id] = graph_element;

			for(size_type i = 0; i < ptr_element->input().size(); ++i)
			{
				graph_element->vInPins[i]->value = ptr_element->input()[i];
			}

			for(size_type i = 0; i < ptr_element->output().size(); ++i)
			{
				graph_element->vOutPins[i]->value = ptr_element->output()[i];
			}

			graph_element->g_x = g_info.position.x;
			graph_element->g_y = g_info.position.y;
			graph_element->width = g_info.size.x;
			graph_element->height = g_info.size.y;

			graph_element->setPos(graph_element->g_x, graph_element->g_y);

			graph_element->id = id;

			graph_element->SetPinsCoords();

			scene->addItem(graph_element);
		}

	}

	for (auto id_ptr : elements)
	{
		connect(id_ptr.second, &GraphElement::coordChanged, this, &SceneDialog::makeCon);
	}

	connect1();

}

void SceneDialog::draw()
{
	std::vector<Lay*> layers;

	elements.clear();

	int lay_counter = 0;
	for (auto& layer : scheme_ptr->circuit())
	{
		auto ptr_lay = new Lay(x0, y0 + lay_counter++ * inter_layer_width);

		int x = 0;

		for (auto id : layer)
		{

			auto g_info = scheme_ptr->graphic_information(id);
			auto ptr_element = scheme_ptr->element(id);

			auto graph_element = new GraphElement(g_info.iosize.in, g_info.iosize.out, ptr_lay);


			elements[id] = graph_element;

			for(size_type i = 0; i < ptr_element->input().size(); ++i)
			{
				graph_element->vInPins[i]->value = ptr_element->input()[i];
			}
			for(size_type i = 0; i < ptr_element->output().size(); ++i)
			{
				graph_element->vOutPins[i]->value = ptr_element->output()[i];
			}

			graph_element->g_x = ptr_lay->pos().x() + x;
			graph_element->g_y = ptr_lay->pos().y();
			graph_element->name = QString(g_info.name.c_str());

			x += inter_element_width + graph_element->get_width();



			graph_element->id = id;

			graph_element->SetPinsCoords();

			ptr_lay->listElements.push_back(graph_element);
		};


		layers.push_back(ptr_lay);
		scene->addItem(ptr_lay);
	}

	QPointF out_pin;
	QPointF in_pin;
	bool is_true;

	for (auto& wire : scheme_ptr->wires())
	{
		out_pin = elements[wire.first.id1]->vOutPins[wire.second.pin1]->GetPoint();
		 in_pin = elements[wire.first.id2]->vInPins[wire.second.pin2]->GetPoint();

		is_true = elements[wire.first.id1]->vOutPins[wire.second.pin1]->value;

		if (is_true){
			scene->addLine(QLineF(out_pin,in_pin), QPen(Qt::red,1));
		}
		else{
			scene->addLine(QLineF(out_pin,in_pin), QPen(Qt::black,1));
		}
	}




}


SceneDialog::~SceneDialog()
{
	delete ui;
}

void SceneDialog::on_draw_clicked()
{
	scene->items().clear();
	scene->clear();
	drawUnstruct();
}

void SceneDialog::on_structurize_clicked()
{
	scene->items().clear();
	scene->clear();
	draw();
}



void SceneDialog::makeCon()
{
	for (int i = 0; i < lines.size(); ++i)
		scene->removeItem(lines[i]);
	lines.clear();
	scene->update();
	connect1();
}

void SceneDialog::on_btnDrawStruct_clicked()
{
	scene->items().clear();
	scene->clear();
	draw();
}
