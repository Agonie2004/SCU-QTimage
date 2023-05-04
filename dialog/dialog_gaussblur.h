#ifndef GAUSSIANBLURDIALOG_H
#define GAUSSIANBLURDIALOG_H
//实现高斯模糊
#include <QDialog>  //QDialog 是 Qt 框架中的一个类，用于实现对话框窗口

namespace Ui {
class GaussianBlurDialog;
}

class GaussianBlurDialog : public QDialog
{
    Q_OBJECT
    //    //Q_OBJECT 是一个宏，它必须出现在使用 Qt 元对象系统的类的声明中
    //使用了 Q_OBJECT 宏，这意味着这个类将会被 Qt 的元对象系统所管理
    //并且可以获得元数据的支持，包括 signals 和 slots 的支持。
public:
    //QWidget 是GUI控件的基类，提供界面布局、事件处理和绘图的基本功能
    explicit GaussianBlurDialog(QWidget *parent = nullptr);
    //nullptr是C++11的关键字，表示指针类型的空指针
    ~GaussianBlurDialog();

private:
    Ui::GaussianBlurDialog *ui;

//信号
signals:
    void sendData(int, double);
//槽
private slots:
    void on_buttonOK_accepted();
};

#endif // GAUSSIANBLURDIALOG_H
