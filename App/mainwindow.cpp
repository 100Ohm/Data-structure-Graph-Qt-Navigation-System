#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlRelationalDelegate>
#include <QCompleter>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置窗口透明度
    setWindowOpacity(0.9);
    //初始化画地点的颜色数组
    initColor();
    //初始化选项框的选项
    initComboBoxItem();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(mytimer()));
    timer->start(5000);

    onShowTML("无","无","无");

    //设置下面的列表框
    tablemodel = new QSqlRelationalTableModel(this);
    tablemodel->setTable("vex");
    tablemodel->select();
    tablemodel->removeColumn(4);
    tablemodel->removeColumn(3);
    tablemodel->removeColumn(2);
    tablemodel->removeColumn(0);
    tablemodel->setHeaderData(0, Qt::Horizontal, QObject::tr("地点名称"));
    tablemodel->setHeaderData(1, Qt::Horizontal, QObject::tr("地点类型"));
    ui->tableView->setModel(tablemodel);
//    QTableView *view = new QTableView(this);
//    view->setModel(model);
//    setCentralWidget(view);
//    view->setItemDelegate(new QSqlRelationalDelegate(view));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tablemodel;
}

void MainWindow::onDraw(DisplayVex vexs[], DisplayEdge edges[], int v, int e){
    //录入数据
    for(int n = 0; n < v; n ++){
        this->vexs[n].id = vexs[n].id;
        this->vexs[n].name = vexs[n].name;
        this->vexs[n].p = vexs[n].p;
    }
    for(int i = 0; i < e; i ++){
        this->edges[i].id = edges[i].id;
        this->edges[i].isHightWay = edges[i].isHightWay;
        this->edges[i].k = edges[i].k;
        this->edges[i].length = edges[i].length;
        this->edges[i].vex1 = edges[i].vex1;
        this->edges[i].vex2 = edges[i].vex2;
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
    for(int i = 0; i < this->vNum; i++){
        int dx = pos.x() - this->vexs[i].p.x();
        int dy = pos.y() - this->vexs[i].p.y();
        int dist = sqrt(dx*dx+dy*dy);
        if(dist < 12){
            QString str = this->n_ctrl->vexToString(vexs[i].id);
            ui->statusBar->showMessage(str,2000);//显示信息
            ui->lineEdit_2->setText(this->vexs[i].name);
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
    case EDGE_COLOR_0://204.204.153不堵-156.79.79堵
        red =  (int)(k * 48 + 156);
        green = (int)(k * 125 + 79);
        blue = (int)(k * 74 + 79);
        break;
    case EDGE_COLOR_1:
        red = (int)((1 - k) * 255);
        green = (int)(k * 64);
        blue = (int)(k * 64);
        break;
    default:
        break;
    }
    return QColor(red, green, blue, 255);
}

void MainWindow::initColor(){
    //颜色们
    //普通点153.179.204
    brush[0].setRed(153);
    brush[0].setGreen(179);
    brush[0].setBlue(214);
    //起点终点235.0.78
    brush[1].setRed(235);
    brush[1].setGreen(0);
    brush[1].setBlue(78);
    //路上的点255.204.51
    brush[2].setRed(255);
    brush[2].setGreen(204);
    brush[2].setBlue(51);
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
             QString find = "已找到\"";
             ui->lineEdit_2->setText(lineEditText);
             ui->statusBar->showMessage(find.append(lineEditText).append("\", 在右方可以开始导航"),2000);
             on_comboBox_2_activated(ui->comboBox_2->currentText());//查找的时候也直接计算路了
             tablemodel->setTable("vex");//改变一下右下角的列表
             tablemodel->setFilter(QString("vexName = '%1'").arg(lineEditText));
             tablemodel->select();
             tablemodel->removeColumn(4);
             tablemodel->removeColumn(3);
             tablemodel->removeColumn(2);
             tablemodel->removeColumn(0);
             tablemodel->setHeaderData(0, Qt::Horizontal, QObject::tr("地点名称"));
             tablemodel->setHeaderData(1, Qt::Horizontal, QObject::tr("地点类型"));
             ui->lineEdit_1->clear();//清空输入框
             return;
         }
     }
     tablemodel->setTable("vex");//改变一下右下角的列表(显示全部点)
     tablemodel->select();
     tablemodel->removeColumn(4);
     tablemodel->removeColumn(3);
     tablemodel->removeColumn(2);
     tablemodel->removeColumn(0);
     tablemodel->setHeaderData(0, Qt::Horizontal, QObject::tr("地点名称"));
     tablemodel->setHeaderData(1, Qt::Horizontal, QObject::tr("地点类型"));
     ui->lineEdit_1->clear();//清空输入框
     ui->statusBar->showMessage(lineEditText.append("? 没找到该地点"),2000);

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
    on_comboBox_2_activated(ui->comboBox_2->currentText());//点选这两个框都会计算路线
}

void MainWindow::mytimer(){
    this->n_ctrl->onTimer();
}

void MainWindow::on_comboBox_2_activated(const QString &arg1)
{//当出行方式完成完成选择之后
    if(ui->lineEdit_2->text() == "")
        return;
    else{//发出寻路请求
        this->f_ctrl->FindRoad(ui->label_2->text(),ui->lineEdit_2->text(),
                               ui->comboBox->currentText(),arg1,
                               this->vexs, this->edges, this->vNum, this->eNum);
    }
}

void MainWindow::onShowRoad(DisplayVex vexs[],DisplayEdge edge[]){
    for(int n = 0; n < vNum; n ++){
        this->vexs[n].color = vexs[n].color;
    }
    for(int i = 0; i < eNum; i ++){
         this->edges[i].color = edge[i].color;
    }
    update();//刷新,会调用paintEvent()函数
}

void MainWindow::setFindRoadController(FindRoadController *fc){
    this->f_ctrl = fc;
}

void MainWindow::onShowTML(QString time, QString money, QString light){
    ui->label_20->setText(time);
    ui->label_21->setText(money);
    ui->label_22->setText(light);
    if(time == "请驾车"){
        ui->statusBar->showMessage("行人不可通过高速路,请选择驾车",2000);
    }
    if(time == "堵车太严重了"){
        ui->statusBar->showMessage("堵车太严重了,根本走不动,换条路试试",2000);
    }

}

void MainWindow::on_pushButton_clicked()
{//开始导航按钮
    on_comboBox_2_activated(ui->comboBox_2->currentText());
}

void MainWindow::on_lineEdit_2_returnPressed()
{//小文本框按回车的响应
    on_comboBox_2_activated(ui->comboBox_2->currentText());
}

void MainWindow::on_pushButton_2_clicked()
{//美食,设置请求码
    int dis = 0, score = 0, money = 0;
    if(ui->comboBox_3->currentText() == "不限制"){
        dis = 0;
    } else if(ui->comboBox_3->currentText() == "5km以内"){
        dis = 5;
    } else if(ui->comboBox_3->currentText() == "5km-10km"){
        dis = 6;
    } else if(ui->comboBox_3->currentText() == "10km以上"){
        dis = 10;
    }

    if(ui->comboBox_4->currentText() == "不限制"){
        score = 0;
    } else if(ui->comboBox_4->currentText() == "5星及以上"){
        score = 5;
    } else if(ui->comboBox_4->currentText() == "4星及以上"){
        score = 4;
    } else if(ui->comboBox_4->currentText() == "3星及以上"){
        score = 3;
    }

    if(ui->comboBox_5->currentText() == "不限制"){
        money = 0;
    } else if(ui->comboBox_5->currentText() == "50元及以下"){
        money = 50;
    } else if(ui->comboBox_5->currentText() == "50-100元"){
        money = 51;
    } else if(ui->comboBox_5->currentText() == "100元以上"){
        money = 100;
    }
    searchFood(dis,score,money);
}

void MainWindow::on_pushButton_4_clicked()
{//超市,设置请求码
    int dis = 0, score = 0;
    bool open = true;
    if(ui->comboBox_6->currentText() == "不限制"){
        dis = 0;
    } else if(ui->comboBox_6->currentText() == "5km以内"){
        dis = 5;
    } else if(ui->comboBox_6->currentText() == "5km-10km"){
        dis = 6;
    } else if(ui->comboBox_6->currentText() == "10km以上"){
        dis = 10;
    }

    if(ui->comboBox_7->currentText() == "不限制"){
        score = 0;
    } else if(ui->comboBox_7->currentText() == "5星及以上"){
        score = 5;
    } else if(ui->comboBox_7->currentText() == "4星及以上"){
        score = 4;
    } else if(ui->comboBox_7->currentText() == "3星及以上"){
        score = 3;
    }

    if(ui->checkBox->isChecked()){
        open = true;
    } else{
        open = false;
    }
    searchSupermarket(dis,score,open);
}

void MainWindow::on_pushButton_6_clicked()
{//酒店,设置请求码
    int dis = 0, score = 0, money = 0;
    if(ui->comboBox_8->currentText() == "不限制"){
        dis = 0;
    } else if(ui->comboBox_8->currentText() == "5km以内"){
        dis = 5;
    } else if(ui->comboBox_8->currentText() == "5km-10km"){
        dis = 6;
    } else if(ui->comboBox_8->currentText() == "10km以上"){
        dis = 10;
    }
    if(ui->comboBox_9->currentText() == "不限制"){
        score = 0;
    } else if(ui->comboBox_9->currentText() == "5星及以上"){
        score = 5;
    } else if(ui->comboBox_9->currentText() == "4星及以上"){
        score = 4;
    } else if(ui->comboBox_9->currentText() == "3星及以上"){
        score = 3;
    }

    if(ui->comboBox_10->currentText() == "不限制"){
        money = 0;
    } else if(ui->comboBox_10->currentText() == "500元及以下"){
        money = 500;
    } else if(ui->comboBox_10->currentText() == "500-1000元"){
        money = 501;
    } else if(ui->comboBox_10->currentText() == "1000元以上"){
        money = 1000;
    }
    searchHotel(dis,score,money);
}

void MainWindow::searchFood(int dis, int score, int money){

    tablemodel->setTable("food");
    tablemodel->setRelation(1, QSqlRelation("vex", "id", "vexName"));
    tablemodel->select();
    tablemodel->removeColumn(0);
    tablemodel->setHeaderData(0, Qt::Horizontal, QObject::tr("美食店名称"));
    tablemodel->setHeaderData(1, Qt::Horizontal, QObject::tr("用户评分"));
    tablemodel->setHeaderData(2, Qt::Horizontal, QObject::tr("人均消费(元)"));
    tablemodel->setHeaderData(3, Qt::Horizontal, QObject::tr("用户评价"));
    float *allRoad = this->f_ctrl->FindAllRoad(ui->label_2->text(),vexs,edges,vNum,eNum);
    for(int n = 0; n < vNum; n ++){
        qDebug() << allRoad[n];
    }
    free(allRoad);
}

void MainWindow::searchSupermarket(int dis, int score, bool open){

    tablemodel->setTable("supermarket");
    tablemodel->setRelation(1, QSqlRelation("vex", "id", "vexName"));
    tablemodel->select();
    tablemodel->removeColumn(0);
    tablemodel->setHeaderData(0, Qt::Horizontal, QObject::tr("超市名称"));
    tablemodel->setHeaderData(1, Qt::Horizontal, QObject::tr("用户评分"));
    tablemodel->setHeaderData(2, Qt::Horizontal, QObject::tr("开店时间"));
    tablemodel->setHeaderData(3, Qt::Horizontal, QObject::tr("关店时间"));
    tablemodel->setHeaderData(4, Qt::Horizontal, QObject::tr("用户评价"));
    float *allRoad = this->f_ctrl->FindAllRoad(ui->label_2->text(),vexs,edges,vNum,eNum);
    for(int n = 0; n < vNum; n ++){
        qDebug() << allRoad[n];
    }
    free(allRoad);
}

void MainWindow::searchHotel(int dis, int score, int money){

    tablemodel->setTable("hotel");
    tablemodel->setRelation(1, QSqlRelation("vex", "id", "vexName"));
    tablemodel->select();
    tablemodel->removeColumn(0);
    tablemodel->setHeaderData(0, Qt::Horizontal, QObject::tr("酒店名称"));
    tablemodel->setHeaderData(1, Qt::Horizontal, QObject::tr("用户评分"));
    tablemodel->setHeaderData(2, Qt::Horizontal, QObject::tr("住店价格(天)"));
    tablemodel->setHeaderData(3, Qt::Horizontal, QObject::tr("用户评价"));
    float *allRoad = this->f_ctrl->FindAllRoad(ui->label_2->text(),vexs,edges,vNum,eNum);
    for(int n = 0; n < vNum; n ++){
        qDebug() << allRoad[n];
    }
    free(allRoad);
}
