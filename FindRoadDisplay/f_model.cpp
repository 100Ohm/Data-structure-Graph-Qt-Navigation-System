#include "f_model.h"

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>

F_Model::F_Model(FindRoadController *c)
{
    this->c = c;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databaseName);
    if (!db.open()) {
        qDebug() << "Unable to establish a database connection." << endl;
    }
}

F_Edge F_Model::loadARoad(int id){
    QSqlQuery query;
    F_Edge e;
    query.exec("select * from edge");
    while(query.next()){
        if(query.value(0).toInt() == id){
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

