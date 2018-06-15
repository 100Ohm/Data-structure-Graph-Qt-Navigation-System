#include "mainwindow.h"
#include <QApplication>
#include "../NormalDisPlay/n_controller.h"
#include "../FindRoadDisplay/f_controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //通常显示
    N_Controller nc(&w);
    //计算路径
    F_Controller fc(&w);
    w.show();
    return a.exec();
}
