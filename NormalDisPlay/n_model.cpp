#include "n_model.h"
#include "../AppStandard/displayedge.h"
#include "../AppStandard/displayvex.h"

#include <QDebug>
#include <QSqlQuery>

N_Model::N_Model(NormalController *c)
{
    this->c = c;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databaseName);
    if (!db.open()) {
        qDebug() << "Unable to establish a database connection." << endl;
    }
}

void N_Model::loadDisplayData(){
    loadDisplayVexAndEdge();//加载点和边
    loadDisplayVexName();//加载地名
}

void N_Model::loadDisplayVexAndEdge(){
    int v = 0, e = 0;
    DisplayVex vexs[MAX_VEX_NUM];
    QSqlQuery query;
    query.exec("select * from vex");
    while(query.next() && v < MAX_VEX_NUM){
        vexs[v].name = query.value(1).toString();
        vexs[v].p.setX((int)(query.value(2).toInt() * 0.7) + 10);
        vexs[v].p.setY((int)(query.value(3).toInt() * 0.7) + 100);
        v ++;
    }

    DisplayEdge edges[MAX_EDGE_NUM];
    QSqlQuery query1;
    query1.exec("select * from edge");
    while(query1.next() &&  e < MAX_EDGE_NUM){
        edges[e].vex1 = query1.value(1).toInt() - 1;
        edges[e].vex2 = query1.value(2).toInt() - 1;
        edges[e].length = query1.value(3).toInt();
        if(query1.value(5).toInt() == 1)
            edges[e].isHightWay = true;
        e ++;
    }
    //刷新界面
    this->c->onDraw(vexs,edges,v,e);
}
void N_Model::loadDisplayVexName(){
    QSqlQuery query;
    QStringList strList;
    query.exec("select * from vex");
    while(query.next()){
        strList.append(query.value(1).toString());
    }
    //设置输入框提示
    this->c->onVexNameChange(strList);
}

QString N_Model::vexToString(int vNum){
    if(this->c == NULL)
        return "";
    int n = 0, id = 0;
    QSqlQuery query;
    QString str = "";
    query.exec("select * from vex");
    while(query.next()){
        if(n == vNum){//第n个地点
            id = query.value(0).toInt();//获得这个点的id
            str.append(query.value(1).toString());
            switch(query.value(5).toInt()){
            case 1://酒店
                query.exec("select * from hotel");
                while(query.next()){
                    if(query.value(1).toInt() == id){
                        str.append(":");
                        str.append(query.value(4).toString());
                        break;
                    }
                }
                break;
            case 2://美食
                query.exec("select * from food");
                while(query.next()){
                    if(query.value(1).toInt() == id){
                        str.append(":");
                        str.append(query.value(4).toString());
                        break;
                    }
                }
                break;
            case 3://超市
                query.exec("select * from supermarket");
                while(query.next()){
                    if(query.value(1).toInt() == id){
                        str.append(":");
                        str.append(query.value(5).toString());
                        break;
                    }
                }
                break;
            case 0:
            default:
                break;
            }
            break;
        }
        n ++;
    }
    return str;
}
