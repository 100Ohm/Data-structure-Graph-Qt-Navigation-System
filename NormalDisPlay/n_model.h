#ifndef N_MODEL_H
#define N_MODEL_H

#include "normaldisplay_global.h"
#include "normalmodel.h"
#include "normalcontroller.h"


class NORMALDISPLAYSHARED_EXPORT N_Model
        :public NormalModel
{
public:
    //从数据库中加载地图显示数据
    void loadDisplayData();
    //获取某一个地点的语言描述
    QString vexToString(int vNum);
    //改变某一个点的xy
    void changeXY(int id, int x, int y);
    N_Model(NormalController *c);
private:
    NormalController *c = NULL;
    void loadDisplayVexAndEdge();//加载点和边
    void loadDisplayVexName();//加载地名
};

#endif // N_MODEL_H
