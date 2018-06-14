#include "n_controller.h"
#include "n_model.h"

N_Controller::N_Controller(NormalDisPlay *view)
{
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
}

void N_Controller::onChangeK(const float new_k[]){
    this->view->onChangeK(new_k);
}

void N_Controller::onVexNameChange(const QStringList strList){
    this->view->onVexNameChange(strList);
}
