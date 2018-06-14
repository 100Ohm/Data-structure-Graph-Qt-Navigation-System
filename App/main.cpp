#include "mainwindow.h"
#include <QApplication>
#include "../NormalDisPlay/n_controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //通常显示
    N_Controller nc(&w);
    w.show();
    return a.exec();
}
