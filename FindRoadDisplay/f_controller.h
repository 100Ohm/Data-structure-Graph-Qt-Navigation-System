#ifndef F_CONTROLLER_H
#define F_CONTROLLER_H
#include "findroaddisplay_global.h"
#include "../AppStandard/appstandard.h"
#include "../AppStandard/displayedge.h"
#include "../AppStandard/displayvex.h"
#include "findroaddisplay.h"
#include "findroadcontroller.h"
#include "findroadmodel.h"
#include "f_edge.h"
#include "graph.h"

class FINDROADDISPLAYSHARED_EXPORT F_Controller : public FindRoadController
{
public:
    F_Controller(FindRoadDisplay *view);
    ~F_Controller();
    //实现接口
    void FindRoad(QString st, QString ed, QString way, QString plan,
            DisplayVex vexs[],DisplayEdge edge[], int v, int e) ;
    float* FindAllRoad(QString st, DisplayVex vexs[],DisplayEdge edge[], int v, int e);
private:
    FindRoadDisplay *view = NULL;
    FindRoadModel *model = NULL;
    int vNum, eNum;
    int wayAndPlan = 0;
    bool isFindAllRoad = false;//是否查找所有道路
    float* analyze(QString st, QString ed, QString way, QString plan,
            DisplayVex vexs[],DisplayEdge edge[], int v, int e) ;
    float* myFindRoad(DisplayVex vexs[],DisplayEdge edge[], int st, int ed);
};

#endif // F_CONTROLLER_H
