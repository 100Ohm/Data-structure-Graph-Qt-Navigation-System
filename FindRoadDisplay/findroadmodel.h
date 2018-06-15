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
    //virtual void getRoadInfo(DisplayEdge edges[], int e) = 0;
};

#endif // FINDROADMODEL_H
