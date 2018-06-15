#include "f_model.h"

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>

F_Model::F_Model(FindRoadController *c)
{
    this->c = c;
}

F_Edge F_Model::loadARoad(int id){
    QSqlQuery query;
    F_Edge e;
    query.exec("select * from edge");
    while(query.next()){
        if(query.value(0).toInt() == id){
            id = query.value(0).toInt();
            e.length = query.value(3).toInt();
            e.speed = query.value(4).toInt();
            e.isHigthway = query.value(5).toInt();
            if(e.isHigthway){
                query.exec("select * from highway");
                while(query.next()){
                    if(query.value(1).toInt() == id){
                        e.money = query.value(2).toInt();
                        break;
                    }
                }
            } else {
                query.exec("select * from OrdinaryRoad");
                while(query.next()){
                    if(query.value(1).toInt() == id){
                        e.light = query.value(2).toInt();
                        break;
                    }
                }
            }
            break;
        }
    }
    return e;
}

F_Edge* F_Model::getRoadInfo(int eNum){
    QSqlQuery query,query1;
    int n = 0, id = 0;
    F_Edge *e = (F_Edge *) malloc(eNum * sizeof(F_Edge));//为数组开辟空间
    query.exec("select * from edge");
    while(query.next()){
        id = query.value(0).toInt();
        e[n].length = query.value(3).toInt();
        e[n].speed = query.value(4).toInt();
        e[n].isHigthway = query.value(5).toInt();
        e[n].time = 0.0;
        if(e[n].isHigthway){
            query1.exec("select * from highway");
            while(query1.next()){
                if(query1.value(1).toInt() == id){
                    e[n].money = query1.value(2).toInt();
                    e[n].light = 0;
                    break;
                }
            }
        } else {
            query1.exec("select * from OrdinaryRoad");
            while(query1.next()){
                if(query1.value(1).toInt() == id){
                    e[n].light = query1.value(2).toInt();
                    e[n].money = 0;
                    break;
                }
            }
        }
        n ++;
    }
    return e;
}
