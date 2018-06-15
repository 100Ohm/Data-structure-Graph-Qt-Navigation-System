#ifndef F_EDGE_H
#define F_EDGE_H

#define BYCAR         0b00000001
#define WALK          0b00000010
#define DISTANCE  0b00000100
#define TIME          0b00001000
#define ROAD          0b00010000
#define MONEY       0b00100000
#define HIGHTWAY 0b01000000
#define NORMAL      0b10000000

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
