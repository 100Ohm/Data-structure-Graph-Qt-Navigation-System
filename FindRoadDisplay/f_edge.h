#ifndef F_EDGE_H
#define F_EDGE_H

#include "findroaddisplay_global.h"
#include "../AppStandard/appstandard.h"
#include "../AppStandard/displayedge.h"
#include "../AppStandard/displayvex.h"
#include "../FindRoadDisplay/findroadcontroller.h"
#include "../FindRoadDisplay/findroadmodel.h"

#define BYCAR         0x00000001
#define WALK          0x00000010
#define DISTANCE  0x00000100
#define TIME          0x00001000
#define ROAD          0x00010000
#define MONEY       0x00100000
#define HIGHTWAY 0x01000000
#define NORMAL      0x10000000

class FINDROADDISPLAYSHARED_EXPORT F_Edge
{
public:
    int length = INF;
    int speed = 30;
    int isHigthway = 0;
    int light = 0;
    int money = 0;
    int weigth = INF;
    F_Edge();
    int getweigth(int ask);
private:

};

#endif // F_EDGE_H
