#include "n_controller.h"
#include "n_model.h"
#include <QDebug>
#include <QTime>

N_Controller::N_Controller(NormalDisPlay *view)
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    this->view = view;
    this->view->setNormalControll(this);
    this->model = new N_Model(this);
    loadDisplayData();
}

N_Controller::~N_Controller(){
    delete (N_Model*)this->model;
    this->model = NULL;
}

void N_Controller::loadDisplayData(){
    this->model->loadDisplayData();
}

QString N_Controller::vexToString(int vNum){
    return this->model->vexToString(vNum);
}

void N_Controller::kNumChange(int n){
    this->kNum = n;
}

void N_Controller::onDraw(DisplayVex vexs[], DisplayEdge edges[], int v, int e){
    this->view->onDraw(vexs, edges, v, e);
    this->kNum = e;
}

void N_Controller::onVexNameChange(const QStringList strList){
    this->view->onVexNameChange(strList);
}

void N_Controller::onTimer(){
    if(kNum == 0)
        return;
    for(int n = 0; n < this->kNum; n++){
        this->k[n] = (float)((int)qrand() %100)/100.0;
    }
    this->view->onChangeK(this->k);
}

void N_Controller::changeVexXY(int id, QPoint p){
    this->model->changeXY(id, p.x(), p.y());
}
