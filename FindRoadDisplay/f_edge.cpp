#include "f_edge.h"

F_Edge::F_Edge()
{

}

float F_Edge::getweigth(int ask){
    if ((ask&WALK) == WALK){
        if(isHigthway == 1){
            this->weigth = (float)INF;
            return weigth;
        }
        this->speed = WALK_SPEED;
        this->time = 60.0 * (this->length/(float)this->speed);//计算速度
    } else {
        float new_speed = (float)this->speed * k;
        this->time = 60.0 * (this->length/(new_speed));//计算速度
    }

    if((ask&DISTANCE) == DISTANCE){
        distance();
    }else if((ask&TIME) == TIME){
        gettime();
    }else if((ask&ROAD) == ROAD){
        road();
    }else if((ask&MONEY) == MONEY){
        getmoney();
    }else if((ask&HIGHTWAY) == HIGHTWAY){
        highway();
    }else if((ask&NORMAL) == NORMAL){;
        normal();
    }
    return this->weigth;
}

void F_Edge::distance(){
    this->weigth = (float)this->length;
}

void F_Edge::gettime(){
    this->weigth = (float)this->time;
}

void F_Edge::road(){
    this->weigth = 1.0;
}

void F_Edge::getmoney(){
    //我改了一下,权值不应该用金钱,
    //因为同样价格的路很多条,我要让它选择最短那条
    if(this->money == 0){
        this->weigth = (float)1.0;
    } else {
        this->weigth = (float)(this->money * 100);
    }
}

void F_Edge::highway(){
    if(this->isHigthway){
        this->weigth = (float)this->length;
    } else {
        this->weigth = (float)(100 * this->length);
    }
}

void F_Edge::normal(){
    if(this->isHigthway){
        this->weigth = (float)(100 * this->length);
    } else {
        this->weigth = (float)(this->length);
    }
}
