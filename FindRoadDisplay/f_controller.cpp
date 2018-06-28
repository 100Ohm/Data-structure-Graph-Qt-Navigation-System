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
        DisplayVex vexs[],DisplayEdge edge[], int v, int e) {//做一些准备工作
    isFindAllRoad = false;
    float *allRoad = analyze(st, ed, way, plan, vexs, edge, v, e);
    free(allRoad);
}

float* F_Controller::FindAllRoad(QString st, DisplayVex vexs[],DisplayEdge edge[], int v, int e){
    isFindAllRoad = true;
    if(st.compare(QString::fromLocal8Bit("君子兰桥"))){
        return analyze(st, "桂花宾馆", "驾车", "距离最短", vexs, edge, v, e);
    } else {
        return analyze(st, "君子兰桥", "驾车", "距离最短", vexs, edge, v, e);
    }
}

float* F_Controller::analyze(QString st, QString ed, QString way, QString plan,
        DisplayVex vexs[],DisplayEdge edge[], int v, int e){//做一些准备工作
    float *allRoad;
    int start = 0, end = 0;
    bool error = false;
    if(st != ed) {
        for(int n = 0; n < v; n ++){//找名字
            if(vexs[n].name.compare(st)){
                start = n;
            }else if(vexs[n].name.compare(ed)){
                end = n;
            }
        }
    } else {
        this->view->onShowTML("无","无","无");
        error = true;
    }
    if(error || start == 0 || end == 0){//如果名字异常
        this->view->onShowTML("无法到达","无法到达","无法到达");
        allRoad = (float *) malloc(v * sizeof(float));
        for(int n = 0; n < v; n ++){
            allRoad[n] = INF;
        }
        return allRoad;
    }
    this->vNum = v;
    this->eNum = e;
    //计算道路权重需要的请求码
    wayAndPlan = 0;
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
    return this->myFindRoad(vexs,edge,start,end);
}

float* F_Controller::myFindRoad(DisplayVex vexs[],DisplayEdge edge[], int st, int ed){
    F_Edge *fe;
    float *allRoad;
    Graph myGraph;//定义一个图
    myGraph.vNum = this->vNum;
    //先把道路们的信息加载到F_Edge数组里
    fe = this->model->getRoadInfo(eNum);
    for(int n = 0; n < this->eNum; n ++){
        fe[n].k = edge[n].k;//设置k
        fe[n].getweigth(this->wayAndPlan);//用请求码获取每一条路的权值
        myGraph.edges[edge[n].vex1][edge[n].vex2] = fe[n].weigth;//把权重信息传给图对象
        myGraph.edges[edge[n].vex2][edge[n].vex1] = fe[n].weigth;
        if(!isFindAllRoad)
            edge[n].color = EDGE_COLOR_0;//重置边的颜色
    }
    if(!isFindAllRoad){
        for(int n = 0; n < this->vNum; n ++){//将顶点颜色重置
            if(vexs[n].color != VEX_COLOR_3){//不能熄灭查询信息的点
                vexs[n].color = VEX_COLOR_0;
            }
        }
    }
    int mymoney = 0,mylights = 0;
    float mytime = 0.0;
    if(!myGraph.getWay(st,ed)){
        if(!isFindAllRoad)
            this->view->onShowTML("无法到达","无法到达","无法到达");
    } else {
        if(!isFindAllRoad){
            int pre = ed, now = ed;
            pre = myGraph.way[ed];
            while(now != st){//点亮中间顶点
                vexs[pre].color = VEX_COLOR_2;
                for(int n = 0; n < eNum; n++){
                    if((edge[n].vex1 == pre && edge[n].vex2 == now)
                            || (edge[n].vex2 == pre && edge[n].vex1 == now)){
                        edge[n].color = EDGE_COLOR_1;
                        mytime += fe[n].time;
                        mymoney += fe[n].money;
                        mylights += fe[n].light;
                    }
                }
                now = pre;
                pre = myGraph.way[pre];
            }
            QString timeInfo = QString::number(mytime,'g',4).append("分钟");
            if(mytime == 1.0/0.0){
                timeInfo = "堵车太严重了";
            }
            this->view->onShowTML(timeInfo,
                                  QString("%1").arg(mymoney).append("元"),
                                  QString("%1").arg(mylights).append("个"));
        }
    }
    if(isFindAllRoad){//返回全部路径
        allRoad = (float *) malloc(vNum * sizeof(float));
        for(int n = 0; n < vNum; n++){
            allRoad[n] = myGraph.allDistance[n];
            //qDebug() << myGraph.allDistance[n];
        }
        return allRoad;
    }
    //点亮起点终点
    vexs[st].color = VEX_COLOR_1;
    vexs[ed].color = VEX_COLOR_1;
    this->view->onShowRoad(vexs,edge);
    free(fe);
    return allRoad;
}
