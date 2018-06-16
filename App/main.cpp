#include "mainwindow.h"
#include "connection.h"
#include "../AppStandard/appstandard.h"
#include "../NormalDisPlay/n_controller.h"
#include "../FindRoadDisplay/f_controller.h"
#include <QApplication>
#include <QStyleFactory>
#include <QPalette>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyle(QStyleFactory::create("fusion"));//设置风格
    QPalette myPalette = a.palette();//设置主题的按钮颜色
    QColor buttoncolor(175,202,202);//175.202.202//153,204,255
    myPalette.setColor(QPalette::Button, buttoncolor);
    a.setPalette(myPalette);

    //打开数据库
    if(!mylinkDatabase())
        exit(1);
    MainWindow w;
    //通常显示
    N_Controller nc(&w);
    //计算路径
    F_Controller fc(&w);
    w.show();
    return a.exec();
}
