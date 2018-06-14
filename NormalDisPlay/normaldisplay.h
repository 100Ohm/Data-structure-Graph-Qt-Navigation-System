#ifndef NORMALDISPLAY_H
#define NORMALDISPLAY_H

#include "normaldisplay_global.h"
#include "../AppStandard/displayvex.h"
#include "../AppStandard/displayedge.h"
#include "normalcontroller.h"

#include <QStringList>

class NORMALDISPLAYSHARED_EXPORT NormalDisPlay
{

public:
    NormalDisPlay();
    //设置Controll
    virtual void setNormalControll(NormalController *fc) = 0;
    //绘制地图
    virtual void onDraw(DisplayVex vexs[], DisplayEdge edges[], int v, int e) = 0;
    //拥塞系数的值改变
    virtual void onChangeK(const float new_k[]) = 0;
    //道路和地点信息,显示在下面
    virtual void onVexNameChange(const QStringList strList) = 0;
};

#endif // NORMALDISPLAY_H
