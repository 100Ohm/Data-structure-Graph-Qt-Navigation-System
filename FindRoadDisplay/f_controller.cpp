#include "f_controller.h"
#include "f_model.h"
#include <QDebug>

F_Controller::F_Controller(FindRoadDisplay *view){
    this->view = view;
    this->view->setFindRoadController(this);
    this->model = new F_Model(this);
}

F_Controller::~F_Controller(){
    delete (F_Model *)this->model;
    this->model = NULL;
}

void F_Controller::FindRoad(QString st, QString ed, QString way, QString plan,
        DisplayVex vexs[],DisplayEdge edge[], int v, int e) {
    qDebug() << st << ed << way << plan << v << e << endl;
    this->vNum = v;
    this->eNum = e;
    //计算道路权重需要的请求码
    if(way == "驾车")
        wayAndPlan = wayAndPlan|BYCAR;
    else if(way == "步行")
        wayAndPlan = wayAndPlan|WALK;
    if(plan == "距离最短")
        wayAndPlan = wayAndPlan|DISTANCE;
    else if(plan == "耗时最少")
        wayAndPlan = wayAndPlan|TIME;
    else if(plan == "经过道路最少")
        wayAndPlan = wayAndPlan|ROAD;
    else if(plan == "花费最少")
        wayAndPlan = wayAndPlan|MONEY;
    else if(plan == "高速优先")
        wayAndPlan = wayAndPlan|HIGHTWAY;
    else if(plan == "非高速优先")
        wayAndPlan = wayAndPlan|NORMAL;
}
