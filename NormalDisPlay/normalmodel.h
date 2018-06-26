#ifndef NORMALMODEL_H
#define NORMALMODEL_H
#include "normaldisplay_global.h"
#include "../AppStandard/appstandard.h"
#include "normalcontroller.h"

class NORMALDISPLAYSHARED_EXPORT NormalModel
{
public:
    //从数据库中加载地图显示数据
    virtual void loadDisplayData() = 0;
    //获取某一个地点的语言描述
    virtual QString vexToString(int vNum) = 0;
    //改变某个点的坐标
    virtual void changeXY(int id, int x, int y) = 0;
    NormalModel();
};

#endif // NORMALMODEL_H
