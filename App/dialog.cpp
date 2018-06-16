#include "dialog.h"
#include "ui_dialog.h"
#include <QSqlRelationalDelegate>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>

Dialog::Dialog(int type,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //设置窗口透明度
    setWindowOpacity(0.85);

    //设置表格
    tablemodel = new QSqlRelationalTableModel(this);
    if(type){
        tablemodel->setTable("edge");
        tablemodel->select();
        tablemodel->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        tablemodel->setHeaderData(1, Qt::Horizontal, QObject::tr("第一个顶点id"));
        tablemodel->setHeaderData(2, Qt::Horizontal, QObject::tr("第二个顶点id"));
        tablemodel->setHeaderData(3, Qt::Horizontal, QObject::tr("路长(千米)"));
        tablemodel->setHeaderData(4, Qt::Horizontal, QObject::tr("限速(千米/小时)"));
        tablemodel->setHeaderData(5, Qt::Horizontal, QObject::tr("道路类型"));
        ui->tableView->setModel(tablemodel);

        ui->comboBox->addItem("全部道路");
        ui->comboBox->addItem("高速公路");
        ui->comboBox->addItem("市内道路");
    }else{
        tablemodel->setTable("vex");
        tablemodel->select();
        tablemodel->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        tablemodel->setHeaderData(1, Qt::Horizontal, QObject::tr("地点名称"));
        tablemodel->setHeaderData(2, Qt::Horizontal, QObject::tr("X"));
        tablemodel->setHeaderData(3, Qt::Horizontal, QObject::tr("Y"));
        tablemodel->setHeaderData(4, Qt::Horizontal, QObject::tr("路的数目"));
        tablemodel->setHeaderData(5, Qt::Horizontal, QObject::tr("地点类型"));
        ui->tableView->setModel(tablemodel);

        ui->comboBox->addItem("全部地点");
        ui->comboBox->addItem("美食");
        ui->comboBox->addItem("超市");
        ui->comboBox->addItem("酒店");
    }

}

Dialog::~Dialog()
{
    delete ui;
    delete tablemodel;
}


void Dialog::on_comboBox_activated(const QString &arg1)
{
    if(arg1 == "全部地点"){
        tablemodel->setTable("vex");
        tablemodel->select();
        tablemodel->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        tablemodel->setHeaderData(1, Qt::Horizontal, QObject::tr("地点名称"));
        tablemodel->setHeaderData(2, Qt::Horizontal, QObject::tr("X"));
        tablemodel->setHeaderData(3, Qt::Horizontal, QObject::tr("Y"));
        tablemodel->setHeaderData(4, Qt::Horizontal, QObject::tr("路的数目"));
        tablemodel->setHeaderData(5, Qt::Horizontal, QObject::tr("地点类型"));
    } else if(arg1 == "美食"){
        tablemodel->setTable("food");
        tablemodel->setRelation(1, QSqlRelation("vex", "id", "vexName"));
        tablemodel->select();
        tablemodel->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        tablemodel->setHeaderData(1, Qt::Horizontal, QObject::tr("美食店名称"));
        tablemodel->setHeaderData(2, Qt::Horizontal, QObject::tr("用户评分"));
        tablemodel->setHeaderData(3, Qt::Horizontal, QObject::tr("人均消费(元)"));
        tablemodel->setHeaderData(4, Qt::Horizontal, QObject::tr("用户评价"));
        ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    } else if(arg1 == "超市"){
        tablemodel->setTable("supermarket");
        tablemodel->setRelation(1, QSqlRelation("vex", "id", "vexName"));
        tablemodel->select();
        tablemodel->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        tablemodel->setHeaderData(1, Qt::Horizontal, QObject::tr("超市名称"));
        tablemodel->setHeaderData(2, Qt::Horizontal, QObject::tr("用户评分"));
        tablemodel->setHeaderData(3, Qt::Horizontal, QObject::tr("开店时间"));
        tablemodel->setHeaderData(4, Qt::Horizontal, QObject::tr("关店时间"));
        tablemodel->setHeaderData(5, Qt::Horizontal, QObject::tr("用户评价"));
        ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    } else if(arg1 == "酒店"){
        tablemodel->setTable("hotel");
        tablemodel->select();
        tablemodel->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        tablemodel->setHeaderData(1, Qt::Horizontal, QObject::tr("酒店名称"));
        tablemodel->setHeaderData(2, Qt::Horizontal, QObject::tr("用户评分"));
        tablemodel->setHeaderData(3, Qt::Horizontal, QObject::tr("住店价格(天)"));
        tablemodel->setHeaderData(4, Qt::Horizontal, QObject::tr("用户评价"));
        ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    } else if(arg1 == "全部道路"){
        tablemodel->setTable("edge");
        tablemodel->select();
        tablemodel->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        tablemodel->setHeaderData(1, Qt::Horizontal, QObject::tr("第一个顶点id"));
        tablemodel->setHeaderData(2, Qt::Horizontal, QObject::tr("第二个顶点id"));
        tablemodel->setHeaderData(3, Qt::Horizontal, QObject::tr("路长(千米)"));
        tablemodel->setHeaderData(4, Qt::Horizontal, QObject::tr("限速(千米/小时)"));
        tablemodel->setHeaderData(5, Qt::Horizontal, QObject::tr("道路类型"));
    }else if(arg1 == "高速公路"){
        tablemodel->setTable("highway");
        tablemodel->select();
        tablemodel->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        tablemodel->setHeaderData(1, Qt::Horizontal, QObject::tr("对应表中的id"));
        tablemodel->setHeaderData(2, Qt::Horizontal, QObject::tr("收费(元)"));
        ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    } else if(arg1 == "市内道路"){
        tablemodel->setTable("OrdinaryRoad");
        tablemodel->select();
        tablemodel->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        tablemodel->setHeaderData(1, Qt::Horizontal, QObject::tr("对应表中的id"));
        tablemodel->setHeaderData(2, Qt::Horizontal, QObject::tr("红绿灯(个)"));
    }
}

void Dialog::on_pushButton_8_clicked()
{//提交修改
    tablemodel->database().transaction();
    if (tablemodel->submitAll()) {
        if(tablemodel->database().commit()) // 提交
            QMessageBox::information(this, tr("tableModel"),
                                     tr("数据修改成功！"));
    } else {
        tablemodel->database().rollback(); // 回滚
        QMessageBox::warning(this, tr("tableModel"),
                             tr("数据库错误: %1").arg(tablemodel->lastError().text()),
                             QMessageBox::Ok);
    }
}

void Dialog::on_pushButton_7_clicked()
{//撤销修改
    tablemodel->revertAll();
}

void Dialog::on_pushButton_5_clicked()
{//增加记录
    // 获得表的行数
    int rowNum = tablemodel->rowCount();
    // 添加一行
    tablemodel->insertRow(rowNum);
    tablemodel->setData(tablemodel->index(rowNum, 0), rowNum+1);
}

void Dialog::on_pushButton_6_clicked()
{
    // 获取选中的行
    int curRow = ui->tableView->currentIndex().row();

    // 删除该行
    tablemodel->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("删除当前行!"),
                                  tr("你确定删除当前行吗？"), QMessageBox::Yes, QMessageBox::No);
    if(ok == QMessageBox::No)
    { // 如果不删除，则撤销
        tablemodel->revertAll();
    } else { // 否则提交，在数据库中删除该行
        tablemodel->submitAll();
    }
}
