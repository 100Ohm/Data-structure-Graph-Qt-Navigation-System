#ifndef NORMALCONTROLLER_H
#define NORMALCONTROLLER_H
#include "normaldisplay_global.h"
#include "../AppStandard/appstandard.h"
#include "../AppStandard/displayedge.h"
#include "../AppStandard/displayvex.h"

class NORMALDISPLAYSHARED_EXPORT NormalController
{
public:
    //面向model
    //绘制地图
    virtual void onDraw(DisplayVex vexs[], DisplayEdge edges[], int v, int e) = 0;
    //道路和地点信息,显示在下面
    virtual void onVexNameChange(const QStringList strList) = 0;

    //面向View
    //从数据库中加载显示地图用的数据
    virtual void loadDisplayData() = 0;
    //获取某一个地点的语言描述
    virtual QString vexToString(int vNum) = 0;
    //view里面计时器跳动时通知controller
    virtual void onTimer() = 0;

    //面向View或Model
    //需要堵塞系数的个数改变
    virtual void kNumChange(int n) = 0;

    NormalController();
};

#endif // NORMALCONTROLLER_H
