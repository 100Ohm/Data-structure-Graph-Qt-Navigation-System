#ifndef FINDROADMODEL_H
#define FINDROADMODEL_H

#include "findroaddisplay_global.h"
#include "../AppStandard/appstandard.h"
#include "../AppStandard/displayedge.h"
#include "f_edge.h"

class FINDROADDISPLAYSHARED_EXPORT FindRoadModel
{
public:
    FindRoadModel();
    //获取一组边的信息
    virtual F_Edge* getRoadInfo(int eNum) = 0;
    //加载一条边的数据
    virtual F_Edge loadARoad(int id) = 0;
};

#endif // FINDROADMODEL_H
