#include "graphicsview.h"

//重写QGraphicsView实现图像的缩放
//QGraphicsView本身并没有实现鼠标滚轮缩放功能，需要重写wheelEvent函数来实现。

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent)
{
}
//它调用了QGraphicsView的构造函数，并将parent作为参数传递给QGraphicsView的构造函数。这里的作用是设置GraphicsView对象的父级窗口

GraphicsView::~GraphicsView()
{
}

//使得鼠标能够实现放大缩小
void GraphicsView::wheelEvent(QWheelEvent *e)
{
    int distance = e->delta()/66;
    //e->delta() 是获取鼠标滚轮旋转的距离，单位为像素，表示滚轮向前滚动还是向后滚动。
    //使用除以 66 的操作将获取到的距离进行调整，使得每个滚动步骤的距离更加合适，从而实现更加平滑的缩放效果。
    
    //如果将除数增大，缩放比例因子会变小，图像缩放会变得更加细微；
    //如果将除数减小，缩放比例因子会变大，图像缩放会相对变得更大。需要根据实际需求进行调整。
    double val;

    if (distance != 0)
    {
        val = pow(1.2, distance);
        //通过计算 pow(1.2, distance) 计算出新的缩放比例，并将其应用到当前视图中，实现了图像的放大缩小。
        this->scale(val, val);
        //this->scale(val, val) 是QGraphicsView中的一个函数，用于缩放视图中的内容。
        //其中val表示缩放系数，这里将x轴和y轴的缩放系数都设置为val，实现等比例缩放。
    }
    //scale函数是QGraphicsView类的成员函数，用于对视图进行缩放操作。它的语法如下：

//void QGraphicsView::scale(qreal sx, qreal sy)
//其中，sx和sy参数分别表示沿x轴和y轴缩放的比例因子。
//例如，如果sx和sy都设置为2.0，则视图会以左上角为基准点放大两倍。如果sx和sy都设置为0.5，则视图会缩小到原来的一半。
}
//在这个函数实现中，我们首先计算了鼠标滚轮滚动的距离(即e->delta()/66)
//然后根据距离计算出需要缩放的比例val。最后，我们调用QGraphicsView的scale函数对当前显示的图像进行缩放


