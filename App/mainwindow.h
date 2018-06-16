#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include "../AppStandard/displayedge.h"
#include "../AppStandard/displayvex.h"
#include "../NormalDisPlay/normaldisplay.h"
#include "../NormalDisPlay/normalcontroller.h"
#include "../FindRoadDisplay/findroaddisplay.h"
#include "../FindRoadDisplay/findroadcontroller.h"

//定义一些十六进制的编码
#define DISTANCE_5                          0x1
#define DISTANCE_5_10                    0x2
#define DISTANCE_10                        0x4
#define SCORE_5                                0x8
#define SCORE_4                                0x10
#define SCORE_3                                0x20
#define FOOD_MONEY_50                 0x40
#define FOOD_MONEY_50_100          0x80
#define FOOD_MONEY_100                0x100
#define OPEN                                      0x200
#define HOTEL_MONEY_500              0x400
#define HOTEL_MONEY_500_1000     0x800
#define HOTEL_MONEY_1000             0x1000
#define NONE_1                                  0x2000
#define NONE_2                                  0x4000
#define NONE_3                                  0x8000

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public NormalDisPlay,public FindRoadDisplay
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //实现接口
    //normal
    void setNormalControll(NormalController *fc);
    void onDraw(DisplayVex vexs[], DisplayEdge edges[], int v, int e);
    void onChangeK(const float new_k[]);
    void onVexNameChange(const QStringList strList);
    //finroad
    void setFindRoadController(FindRoadController *fc);
    void onShowRoad(DisplayVex vexs[],DisplayEdge edge[]);
    void onShowTML(QString time, QString money, QString light);

private:
    Ui::MainWindow *ui;
    QColor brush[4];                                      //颜色
    int comboItemNum = 6;                            //出行方案选项个数

    QColor getRoadColor(int color, float k);     //计算路的颜色
    void initColor();                                         //初始化颜色
    void initComboBoxItem();                          //初始化各个选择框的选项

private:
    int vNum = 0, eNum = 0;                             //边和点的数目
    DisplayEdge edges[MAX_EDGE_NUM];      //显示边集
    DisplayVex vexs[MAX_VEX_NUM];           //显示点集
    NormalController *n_ctrl;                             //平时显示的controller
    FindRoadController *f_ctrl;                          //寻找路的controller
    QSqlRelationalTableModel *tablemodel;        //数据库模型
//    void searchFood(int ask);                               //查找美食
//    void searchSupermarket(int ask);                    //查找超市
//    void searchHotel(int ask);                               //查找酒店
    void searchFood(int dis, int score, int money);                               //查找美食
    void searchSupermarket( int dis, int score, bool open);                    //查找超市
    void searchHotel(int dis, int score, int money);                               //查找酒店

protected:
    void paintEvent(QPaintEvent* event);                //绘制地图的函数
    void mousePressEvent(QMouseEvent *event);   //鼠标按下事件

private slots://按钮响应
    void mytimer();
    void on_pushButton_3_clicked();
    void on_lineEdit_1_returnPressed();
    void on_comboBox_activated(const QString &arg1);
    void on_comboBox_2_activated(const QString &arg1);
    void on_pushButton_clicked();
    void on_lineEdit_2_returnPressed();
    void on_pushButton_2_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_4_clicked();
};

#endif // MAINWINDOW_H
