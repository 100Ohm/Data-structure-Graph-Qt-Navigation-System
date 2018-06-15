#ifndef FINDROADCONTROLLER_H
#define FINDROADCONTROLLER_H
#include "findroaddisplay_global.h"
#include "../AppStandard/appstandard.h"
#include "../AppStandard/displayedge.h"
#include "../AppStandard/displayvex.h"
#include "f_edge.h"

class FINDROADDISPLAYSHARED_EXPORT FindRoadController
{
public:
    //面向View
    //view向controller发送寻路请求
    virtual void FindRoad(QString st, QString ed, QString way, QString plan,
            DisplayVex vexs[],DisplayEdge edge[], int v, int e) = 0;

    //面向Model
    //virtual void roadInfo(F_Edge edges[], int e) = 0;

    FindRoadController();
};

#endif // FINDROADCONTROLLER_H
