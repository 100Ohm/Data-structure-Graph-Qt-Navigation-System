#ifndef F_EDGE_H
#define F_EDGE_H

//定义一些十六进制的编码
#define BYCAR         0x1
#define WALK          0x2
#define DISTANCE  0x4
#define TIME          0x8
#define ROAD          0x10
#define MONEY       0x20
#define HIGHTWAY 0x40
#define NORMAL      0x80

#define WALK_SPEED 5

#include "findroaddisplay_global.h"
#include "../AppStandard/appstandard.h"
#include "../AppStandard/displayedge.h"
#include "../AppStandard/displayvex.h"

class FINDROADDISPLAYSHARED_EXPORT F_Edge
{
public:
    int length = INF;
    int speed = 5;
    int isHigthway = 0;
    int light = 0;
    float weigth = INF;
    float time = 0;
    int money = 0;
    float k = 1.0;
    F_Edge();
    float getweigth(int ask);
private:
    void distance();
    void gettime();
    void road();
    void getmoney();
    void highway();
    void normal();
};

#endif // F_EDGE_H
