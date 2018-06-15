#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <../AppStandard/displayedge.h>
#include <../AppStandard/displayvex.h>
#include <../NormalDisPlay/normaldisplay.h>
#include <../NormalDisPlay/normalcontroller.h>
#include <../FindRoadDisplay/findroaddisplay.h>
#include <../FindRoadDisplay/findroadcontroller.h>


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

protected:
    void paintEvent(QPaintEvent* event);                //绘制地图的函数
    void mousePressEvent(QMouseEvent *event);   //鼠标按下事件

private slots:
    void mytimer();
    void on_pushButton_3_clicked();
    void on_lineEdit_1_returnPressed();
    void on_comboBox_activated(const QString &arg1);
    void on_comboBox_2_activated(const QString &arg1);
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
