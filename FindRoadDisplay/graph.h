#ifndef GRAPH_H
#define GRAPH_H
#include "findroaddisplay_global.h"
#include "../AppStandard/appstandard.h"
#include "../FindRoadDisplay/findroadcontroller.h"

class FINDROADDISPLAYSHARED_EXPORT Graph
{
public:
    int vNum = 0;
    float edges[MAX_VEX_NUM][MAX_VEX_NUM];
    int way[MAX_VEX_NUM];//储存最短路径各点下标
    Graph();
    bool getWay(int start, int end);
};

#endif // GRAPH_H
