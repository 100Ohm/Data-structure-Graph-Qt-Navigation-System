#ifndef DISPLAYVEX_H
#define DISPLAYVEX_H

#include "appstandard.h"
#include <QString>
#include <QPoint>

class APPSTANDARDSHARED_EXPORT DisplayVex
{
public:
    DisplayVex();
    int id = 0;//对应数据库的id!
    QPoint p;//这个点的位置
    int color = VEX_COLOR_0;//上面三个颜色
    QString name = "";//这个点的名字
};

#endif // DISPLAYVEX_H
