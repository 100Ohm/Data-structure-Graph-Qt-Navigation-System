#include "n_model.h"
#include "../AppStandard/displayedge.h"
#include "../AppStandard/displayvex.h"

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>

N_Model::N_Model(NormalController *c)
{
    this->c = c;
}

void N_Model::loadDisplayData(){
    loadDisplayVexAndEdge();//加载点和边
    loadDisplayVexName();//加载地名
}

void N_Model::loadDisplayVexAndEdge(){
    int v = 0, e = 0;
    float k[MAX_EDGE_NUM];
    DisplayVex vexs[MAX_VEX_NUM];
    QSqlQuery query;
    query.exec("select * from vex");
    while(query.next() && v < MAX_VEX_NUM){
        vexs[v].id = query.value(0).toInt();//确定该点id
        vexs[v].name = query.value(1).toString();
        vexs[v].p.setX(query.value(2).toInt());
        vexs[v].p.setY(query.value(3).toInt());
        v ++;
    }

    DisplayEdge edges[MAX_EDGE_NUM];
    QSqlQuery query1;
    query1.exec("select * from edge");
    while(query1.next() &&  e < MAX_EDGE_NUM){
        edges[e].id = query1.value(0).toInt();//确定该边的id
        for(int i = 0; i < v; i ++){//此时v已经是点的个数了
            if(query1.value(1).toInt() == vexs[i].id){
                edges[e].vex1 = i;//确定依赖顶点在数组中的位置
            }
            if(query1.value(2).toInt() == vexs[i].id){
                edges[e].vex2 = i;
            }
        }
        edges[e].length = query1.value(3).toInt();
        if(query1.value(5).toInt() == 1)
            edges[e].isHightWay = true;
        k[e] = (float)(qrand() % 100) / 100.0;//初始化随机堵塞系数k
        edges[e].k = k[e];
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
    int n = 1;
    QSqlQuery query;
    QString str = "";
    query.exec("select * from vex");
    while(query.next()){
        if(n == vNum){//id是对的话
            str.append(query.value(1).toString());
            switch(query.value(5).toInt()){
            case 1://酒店
                query.exec("select * from hotel");
                while(query.next()){
                    if(query.value(1).toInt() == vNum){
                        str.append(":");
                        str.append(query.value(4).toString());
                        break;
                    }
                }
                break;
            case 2://美食
                query.exec("select * from food");
                while(query.next()){
                    if(query.value(1).toInt() == vNum){
                        str.append(":");
                        str.append(query.value(4).toString());
                        break;
                    }
                }
                break;
            case 3://超市
                query.exec("select * from supermarket");
                while(query.next()){
                    if(query.value(1).toInt() == vNum){
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

void N_Model::changeXY(int id, int x, int y){
    QSqlQuery sql_query;
    QString update_sql = "update vex set x = :x , y = :y where id = :id";
    sql_query.prepare(update_sql);
    sql_query.bindValue(":x", x);
    sql_query.bindValue(":y", y);
    sql_query.bindValue(":id", id);
    if(!sql_query.exec())
    {
        qDebug()<<"error";
    }
    else
    {
        qDebug()<<"updated!";
    }
}
