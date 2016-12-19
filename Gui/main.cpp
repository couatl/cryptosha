#include "mainwindow.h"
//#include "../QtCryptosha/easylogging++.h"
#include <QApplication>


//INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.draw();
    w.show();

	//LOG(INFO) << "My first info log using default logger";

    return a.exec();
}
