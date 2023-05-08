#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>     //用于创建主窗口的类
#include <QProcess>        //用于控制外部进程的类
#include <QGraphicsPixmapItem>  //用于在图形视图中显示像素图像的类
#include <QFileDialog>       //用于打开和保存文件对话框的类
#include <QMessageBox>    //用于显示对话框和消息框的类
#include <QInputDialog>    //用于显示输入对话框的类
#include <QLabel>     //用于在窗口中显示文本和图像的类
#include <QDebug>     //用于在控制台中输出调试信息的函数
#include <QStandardPaths>     //用于获取各种系统和应用程序目录的类
#include <QTranslator>     //用于翻译应用程序的类
#include "graphicsview.h"    //显示图形和操作图形视图
#include "../dialog/dialog_gaussblur.h"
#include "../dialog/aboutdialog.h"
#include "../tools/algorithm.h"
#include "../tools/gaussblur.h"
#define WINDOW_TITLE    "SCU-QTimage"
#define WINDOW_ERROR "ERROR"
#define WINDOW_WARNING  "SCU-QTimage"
#define WINDOW_ABOUT    "SCU-QTimage"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateRightImage(QPixmap &pixmap);
    void cleanImage();
    void setActionStatus(bool);
    void createToolBar();
    void closeEvent(QCloseEvent *);

private slots:

    // 从子对话框中接收数据
    void receiveGaussValue(int radius, double sigma);

    void on_doOpen_triggered();//打开文件
    void on_doClose_triggered(); //关闭图片
    void on_doSave_triggered();//保存
    void on_doSave_As_triggered();//另存为
    void on_doExit_triggered(); //退出
    void on_doGrayscale_triggered(); //灰度图像
    void on_doBrightness_triggered();//调整亮度
    void on_doRestore_triggered();//恢复右边图像
    void on_doCool_triggered();//冷
    void on_doWarm_triggered();//温
    void on_doZoom_triggered();         // 缩放
    void on_doHorizontal_triggered();//水平翻转
    void on_doVertical_triggered();//垂直翻转
    void on_doAbout_triggered(); // 关于
    void on_do_adjust_triggered();// 调整图片适应窗口
    void on_do_adjust_left_triggered();// 调整图片适应左窗口
    void on_do_adjust_right_triggered();// 调整图片适应右窗口
    void on_doRotate_triggered();//旋转
    void on_doRotate_left_triggered();//逆时针旋转90度
    void on_doRotate_right_triggered();//顺时针旋转90度
    void on_doSimple_triggered();//简单平滑
    void on_doGauss_triggered();//高斯平滑

    void update_stateBar();

private:

    Ui::MainWindow  *ui;
    //左右两个图片
    //QGraphicsScene是QT中用于管理图形视图的场景的类。
    //QGraphicsScene继承自QGraphicsItem,用于组织和管理添加到其中的图形项。
    QGraphicsScene  *leftScene;
    QGraphicsScene  *rightScene;
    //QGraphicsPixmapItem继承自QGraphicsItem,用于在QGraphicsScene中表示一个图像。它加载和显示一个QPixmap对象中的图像。
    QGraphicsPixmapItem* leftPixmapItem;
    QGraphicsPixmapItem* rightPixmapItem;

    //图片大小label
    QLabel *size;
    //图片像素
    QLabel *Pixel;
    //文件信息读取
    QFileInfo *info;
    //用于存放图片地址（下次打开，保存，另存）
    QString ConstImage;
    //是否修改图片
    bool flag;
    //用于获取桌面位置
    QString getUserPath();
};

#endif // MAINWINDOW_H
