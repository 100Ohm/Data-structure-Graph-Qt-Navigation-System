#ifndef FINDROADCONTROLLER_H
#define FINDROADCONTROLLER_H
#include "findroaddisplay_global.h"
#include "f_edge.h"
#include "../AppStandard/appstandard.h"
#include "../AppStandard/displayedge.h"
#include "../AppStandard/displayvex.h"

class FINDROADDISPLAYSHARED_EXPORT FindRoadController
{
public:
    //面向View
    //view向controller发送寻路请求
    virtual void FindRoad(QString st, QString ed, QString way, QString plan,
            DisplayVex vexs[],DisplayEdge edge[], int v, int e) = 0;
    //找到所有的路
    virtual float* FindAllRoad(QString st, DisplayVex vexs[],DisplayEdge edge[], int v, int e) = 0;

    //面向Model

    FindRoadController();
};

#endif // FINDROADCONTROLLER_H
