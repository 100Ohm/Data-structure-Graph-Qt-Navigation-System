#include "graph.h"

Graph::Graph()
{
    for(int n = 0; n < MAX_VEX_NUM; n ++){
        for(int m = 0; m < MAX_VEX_NUM; m ++){
            this->edges[n][m] = INF;
        }
    }
}

bool Graph::getWay(int start, int end){//迪杰特斯拉算法
    if(start > this->vNum || end > this->vNum)
        return false;
    int i;
    int minVex = -1,minRoad = INF;
    float work[MAX_VEX_NUM];//保存当前到该地点权值之和的工作数组
    //初始化
    for(i = 0; i < this->vNum; i ++){//初始化工作数组
        if(edges[start][i] < INF)
            work[i] = edges[start][i];
        else
            work[i] = INF;
        this->way[i] = start;//前驱标记为start
    }//初始化结束
    work[start] = 0;//权值之和标记为0表示已知顶点
    for(i = 0; i < this->vNum; i++){//找出离第一个点最近的未知点minVex
        if(work[i] < minRoad && work[i] != 0){
            minRoad = work[i];
            minVex = i;
        }
    }//寻找第一个minVex
    while(minVex != -1) {//如果离这个点最近的未知点minVex存在的话
        for(i = 0; i < this->vNum; i ++){//刷新工作数组
            if(work[minVex] + edges[minVex][i] < work[i]){//如果让minVex作为跳板距离更短的话
                work[i] = work[minVex] + edges[minVex][i];//i路长等于到minVex的路加上minVex到i的路
                this->way[i] = minVex;//让i的前驱变为minVex
            }
        }//刷新完工作数组
        work[minVex] = 0;//minVex任务完成,标记为已知
        //找下一个最近的已知顶点MinVex
        minRoad = INF;//重置minRoad的值
        minVex = -1;
        for(i = 0; i < this->vNum; i++){
            if(work[i] < minRoad && work[i] != 0){
                minRoad = work[i];
                minVex = i;
            }
        }//确定完下一个minVex
    }//while完成
    if(work[end] == INF){
        return false;//没有这条路
    } else {
        return true;
    }
}
