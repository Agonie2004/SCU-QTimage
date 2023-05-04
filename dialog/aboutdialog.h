#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>  //用于创建GUI界面的对话框控件
#include<QLabel>  //用于创建GUI界面的标签控件

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT
    //Q_OBJECT 是一个宏，它必须出现在使用 Qt 元对象系统的类的声明中
    //使用了 Q_OBJECT 宏，这意味着这个类将会被 Qt 的元对象系统所管理
    //并且可以获得元数据的支持，包括 signals 和 slots 的支持。
public:
    //QWidget 是GUI控件的基类，提供界面布局、事件处理和绘图的基本功能
    explicit AboutDialog(QWidget *parent = nullptr); //显式转换方式
    //nullptr是C++11的关键字，表示指针类型的空指针
    ~AboutDialog();

private slots://创建于signals相关联的处理程序
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::AboutDialog *ui;
};
//Ui：：AboutDialog用于连接.ui文件中定义的窗口小部件和布局的访问权限

#endif // ABOUTDIALOG_H
