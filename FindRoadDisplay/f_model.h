#ifndef F_MODEL_H
#define F_MODEL_H
#include "findroaddisplay_global.h"
#include "../AppStandard/appstandard.h"
#include "../AppStandard/displayedge.h"
#include "../AppStandard/displayvex.h"
#include "../FindRoadDisplay/findroadcontroller.h"
#include "../FindRoadDisplay/findroadmodel.h"

class FINDROADDISPLAYSHARED_EXPORT F_Model : public FindRoadModel
{
public:
    F_Model(FindRoadController *c);
    //实现接口
    //void getRoadInfo(DisplayEdge edges[], int e);
private:
    FindRoadController *c = NULL;
    F_Edge loadARoad(int id);//加载一条边的数据
};

#endif // F_MODEL_H
