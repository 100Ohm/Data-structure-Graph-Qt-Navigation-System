#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCompleter>
#include <QPainter>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置窗口透明度
    setWindowOpacity(1.0);
    //初始化画地点的颜色数组
    initColor();
    //初始化选项框的选项
    initComboBoxItem();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDraw(DisplayVex vexs[], DisplayEdge edges[], int v, int e){
    for(int n = 0; n < v; n ++){
        this->vexs[n] = vexs[n];
    }
    for(int i = 0; i < e; i ++){
         this->edges[i] = edges[i];
    }
    this->vNum = v;
    this->eNum = e;
    update();//刷新,会调用paintEvent()函数
}

void MainWindow::onChangeK(const float new_k[]){
    for(int i = 0; i < this->eNum; i ++){
         this->edges[i].k = new_k[i];
    }
    update();//刷新,会调用paintEvent()函数
}

void MainWindow::onVexNameChange(const QStringList strList){
    //设置两个输入框的输入提示
    QCompleter* completer = new QCompleter(strList);        // 将字符串列表应用于匹配规则
    completer->setFilterMode(Qt::MatchContains);                // 设置匹配模式为包含匹配
    ui->lineEdit_1->setCompleter(completer);
    ui->lineEdit_2->setCompleter(completer);
}

void  MainWindow::paintEvent(QPaintEvent* event)
{
     QPainter painter(this);

     //画道路
     for(int i = 0; i < this->eNum; i ++)
     {
             if(this->edges[i].length == INF)
                 continue;

             QPoint s(this->vexs[this->edges[i].vex1].p);
             QPoint e(this->vexs[this->edges[i].vex2].p);
             QPoint tpos;//路长度显示位置
             tpos.setX((s.x()+e.x())/2);
             tpos.setY((s.y()+e.y())/2);

             QPen pen(getRoadColor(this->edges[i].color, this->edges[i].k));
             if(this->edges[i].isHightWay)
                 pen.setWidth(5);
             else
                pen.setWidth(3);
             painter.setPen(pen);
             painter.drawLine(s,e);

             QPen pen1(QColor(32, 24, 64));
             pen1.setWidth(5);
             painter.setPen(pen1);
             painter.setFont(QFont("Consolas",10));
             painter.drawText(tpos,QString::number(this->edges[i].length));
     }

     //画地点
     for(int i = 0;  i < this->vNum; i ++)
     {
         QPoint c(this->vexs[i].p);

         painter.setBrush(brush[this->vexs[i].color]);
         painter.setPen(QPen(QColor(255,255,255,0)));
         painter.drawEllipse(c,12,12);

         QPen pen(QColor(54, 52, 51));
         pen.setWidth(4);
         painter.setPen(pen);
         painter.setFont(QFont("微软雅黑",7));
         QPoint tc(c.x() - 4 * this->vexs[i].name.length(),c.y() - 17);
         painter.drawText(tc, this->vexs[i].name);
     }
}

void MainWindow::mousePressEvent(QMouseEvent *event){//鼠标按下事件
    QPoint pos = event->pos();
    int choosedVex = -1;
    for(int i = 0; i < this->vNum; i++){
        int dx = pos.x() - this->vexs[i].p.x();
        int dy = pos.y() - this->vexs[i].p.y();
        int dist = sqrt(dx*dx+dy*dy);
        if(dist < 12){
            choosedVex = i;
            QString str = this->n_ctrl->vexToString(choosedVex);
            ui->statusBar->showMessage(str,2000);
            ui->lineEdit_2->setText(this->vexs[choosedVex].name);
            break;
        }
    }
}

void MainWindow::setNormalControll(NormalController *fc){
    this->n_ctrl = fc;
}

QColor MainWindow::getRoadColor(int color, float k){
    //计算颜色
    int red = 0;
    int green = 0;
    int blue = 0;
    switch(color){
    case EDGE_COLOR_0:
        red = (int)((1 - k) * 255);
        green = (int)(k * 128);
        blue = (int)(k * 128);
        break;
    case EDGE_COLOR_1:
        red = (int)(128 + (1 - k) * 127);
        green = (int)(k * 128);
        blue = (int)(128 + (1 - k) * 127);
        break;
    default:
        break;
    }
    return QColor(red, green, blue, 255);
}

void MainWindow::initColor(){
    //颜色们
    //普通点102.102.245
    brush[0].setRed(61);
    brush[0].setGreen(102);
    brush[0].setBlue(204);
    //起点终点255.51.102
    brush[1].setRed(255);
    brush[1].setGreen(51);
    brush[1].setBlue(102);
    //路上的点255.51.204
    brush[2].setRed(255);
    brush[2].setGreen(51);
    brush[2].setBlue(204);
    //查询信息获得的点255.204.51
    brush[3].setRed(255);
    brush[3].setGreen(204);
    brush[3].setBlue(51);
}

void MainWindow::initComboBoxItem(){
    ui->comboBox->addItem("驾车");
    ui->comboBox->addItem("步行");

    ui->comboBox_2->addItem("距离最短");
    ui->comboBox_2->addItem("耗时最少");
    ui->comboBox_2->addItem("经过道路最少");
    ui->comboBox_2->addItem("花费最少");
    ui->comboBox_2->addItem("高速优先");
    ui->comboBox_2->addItem("非高速优先");

    ui->comboBox_3->addItem("不限制");
    ui->comboBox_3->addItem("5km以内");
    ui->comboBox_3->addItem("5km-10km");
    ui->comboBox_3->addItem("10km以上");

    ui->comboBox_4->addItem("不限制");
    ui->comboBox_4->addItem("5星及以上");
    ui->comboBox_4->addItem("4星及以上");
    ui->comboBox_4->addItem("3星及以上");

    ui->comboBox_5->addItem("不限制");
    ui->comboBox_5->addItem("50元及以下");
    ui->comboBox_5->addItem("50-100元");
    ui->comboBox_5->addItem("100元以上");

    ui->comboBox_6->addItem("不限制");
    ui->comboBox_6->addItem("5km以内");
    ui->comboBox_6->addItem("5km-10km");
    ui->comboBox_6->addItem("10km以上");

    ui->comboBox_7->addItem("不限制");
    ui->comboBox_7->addItem("5星及以上");
    ui->comboBox_7->addItem("4星及以上");
    ui->comboBox_7->addItem("3星及以上");

    ui->comboBox_8->addItem("不限制");
    ui->comboBox_8->addItem("5km以内");
    ui->comboBox_8->addItem("5km-10km");
    ui->comboBox_8->addItem("10km以上");

    ui->comboBox_9->addItem("不限制");
    ui->comboBox_9->addItem("5星及以上");
    ui->comboBox_9->addItem("4星及以上");
    ui->comboBox_9->addItem("3星及以上");

    ui->comboBox_10->addItem("不限制");
    ui->comboBox_10->addItem("500元及以下");
    ui->comboBox_10->addItem("500-1000元");
    ui->comboBox_10->addItem("1000元以上");

    ui->checkBox->setChecked(true);
}

void MainWindow::on_pushButton_3_clicked()
{//"查找地点"按钮
    // 获取搜索框文本
     QString lineEditText = ui->lineEdit_1->text();
     for(int n = 0; n < vNum; n ++){
         if(lineEditText == this->vexs[n].name){
             ui->lineEdit_2->setText(lineEditText);
             ui->statusBar->showMessage("已找到该地点,在右方可以开始导航",2000);
             return;
         }
     }
     ui->statusBar->showMessage("没找到该地点",2000);

}

void MainWindow::on_lineEdit_1_returnPressed()
{
    on_pushButton_3_clicked();
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    for(int i = 0; i < this->comboItemNum; i ++){
        ui->comboBox_2->removeItem(0);
    }
    if(arg1 == "驾车"){
        ui->comboBox_2->addItem("距离最短");
        ui->comboBox_2->addItem("耗时最少");
        ui->comboBox_2->addItem("经过道路最少");
        ui->comboBox_2->addItem("花费最少");
        ui->comboBox_2->addItem("高速优先");
        ui->comboBox_2->addItem("非高速优先");
        this->comboItemNum = 6;
    } else if(arg1 == "步行") {
        ui->comboBox_2->addItem("距离最短");
        ui->comboBox_2->addItem("耗时最少");
        ui->comboBox_2->addItem("经过道路最少");
        this->comboItemNum = 3;
    }
}
