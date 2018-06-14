#ifndef DISPLAYEDGE_H
#define DISPLAYEDGE_H
#include "appstandard.h"

class APPSTANDARDSHARED_EXPORT DisplayEdge
{
public:
    DisplayEdge();
    int length = INF;//路的长度(千米)
    int vex1 = 0,vex2 = 0;//依赖的点
    float k = 1.0;//堵塞系数
    bool isHightWay = false;//是否高速路
    int color = EDGE_COLOR_0;//颜色
};

#endif // DISPLAYEDGE_H
