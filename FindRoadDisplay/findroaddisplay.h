#ifndef FINDROADDISPLAY_H
#define FINDROADDISPLAY_H

#include <QStringList>

#include "findroaddisplay_global.h"
#include "../AppStandard/appstandard.h"
#include "../AppStandard/displayedge.h"
#include "../AppStandard/displayvex.h"
#include "../FindRoadDisplay/findroadcontroller.h"

class FINDROADDISPLAYSHARED_EXPORT FindRoadDisplay
{
public:
    FindRoadDisplay();
    //设置controller
    virtual void setFindRoadController(FindRoadController *fc) = 0;
    //高亮显示查找到的路线
    virtual void onShowRoad(DisplayVex vexs[],DisplayEdge edge[]) = 0;
    //显示时间,金钱红绿灯数量
    virtual void onShowTML(QString time, QString money, QString light) = 0;
};

#endif // FINDROADDISPLAY_H
