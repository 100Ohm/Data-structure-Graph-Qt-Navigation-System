#ifndef APPSTANDARD_H
#define APPSTANDARD_H

#include "appstandard_global.h"
#include <QString>

#define EDGE_COLOR_0 0 //平时颜色
#define EDGE_COLOR_1 1 //查找到路径的颜色
#define VEX_COLOR_0 0 //平时颜色
#define VEX_COLOR_1 1 //起点终点颜色
#define VEX_COLOR_2 2 //路上的颜色
#define VEX_COLOR_3 3 //查信息时候高亮颜色
#define MAX_EDGE_NUM 128 //道路数目最大值
#define MAX_VEX_NUM 64 //地点数目最大值
#define INF 65535 //道路长度最大值

static QString databaseName = "myGraph.db";//数据库名称

class APPSTANDARDSHARED_EXPORT AppStandard
{
};

#endif // APPSTANDARD_H
