#ifndef N_CONTROLLER_H
#define N_CONTROLLER_H
#include "normaldisplay_global.h"
#include "normaldisplay.h"
#include "normalmodel.h"
#include "normalcontroller.h"
/**
 * @brief The N_Controller class
 * 暂时还没写随时间变化生成k数组的代码
 */
class NORMALDISPLAYSHARED_EXPORT N_Controller
        :public NormalController
{
public:
    N_Controller(NormalDisPlay *view);
    ~N_Controller();
    //从数据库中加载显示地图用的数据
    void loadDisplayData();
    //获取某一个地点的语言描述
    QString vexToString(int vNum);
    //需要堵塞系数的个数改变
    void kNumChange(int n);
    //绘制地图
    void onDraw(DisplayVex vexs[], DisplayEdge edges[], int v, int e);
    //道路和地点信息,显示在下面
    void onVexNameChange(const QStringList strList);
    //计时器通知
    void onTimer();
private:
    NormalDisPlay *view = NULL;
    NormalModel *model = NULL;
    int kNum = 0;
    float k[MAX_VEX_NUM];
};

#endif // N_CONTROLLER_H
