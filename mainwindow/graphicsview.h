#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>  //用于创建可视化界面，并支持鼠标、键盘等用户输入事件的处理
#include  <QWheelEvent> //用于处理鼠标滚轮事件
#include <QtMath>

//重写QGraphicsView实现图像的缩放
//QGraphicsView本身并没有实现鼠标滚轮缩放功能，需要重写wheelEvent函数来实现。
class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QWidget* parent = nullptr);//指定GraphicsView对象的父级窗口
    
    //QWidget是Qt中所有用户界面类的基类。在这里，parent指针表示新建的GraphicsView对象将作为哪个QWidget对象的子窗口
    //从而获得相应的窗口管理和继承等特性。

    //在这里，=nullptr是一个默认参数，表示如果构造函数调用时没有传入对应的参数，
    //则默认设置parent指针为空指针，即该GraphicsView对象没有父级窗口。
    //因此，这段代码实现了一个可以选择父级窗口的构造函数，并提供了一个默认值。如果没有传入父级窗口，则该对象不属于任何父级窗口。
    ~GraphicsView();

protected:
    virtual void wheelEvent(QWheelEvent *e);
};
//QWheelEvent是Qt框架中的一个事件类，代表鼠标滚轮事件。
//当用户使用鼠标滚轮进行操作时，QWheelEvent对象就会被创建并传递给对应的窗口或部件。

//QWheelEvent中包含了很多有用的信息，例如滚轮的滚动方向、滚动的幅度值以及鼠标指针当前所在位置等。
//通过处理这些信息，我们可以实现各种响应鼠标滚轮事件的功能，比如图像缩放、滚动条滚动等。

//在GraphicsView类中，我们重写了wheelEvent函数来实现图像的缩放。
//QWheelEvent *e参数将提供关于当前鼠标滚轮事件的所有信息，
//我们可以根据这些信息来计算需要放大或缩小的比例，并将其应用到当前正在显示的图像上。



#endif // GRAPHICSVIEW_H
