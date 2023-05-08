#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include<QProcess>  //QProcess是Qt库中用来调用外部进程的类，可以使用它来启动并与其他进程进行通信
#include <QImage>  //QImage 是 Qt 库中用于处理图像的类，它可以将图像从多种格式（例如 BMP、PNG、JPG 等）加载到内存中
                   //并提供许多操作图像的常用方法（例如调整大小、裁剪、旋转、过滤等） 与 QPixmap 相比更高级
AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
  //创建一个 Ui::AboutDialog 对象，以便通过该对象来访问 UI 文件中定义的各个控件对象
{
    ui->setupUi(this);
    //调用 ui->setupUi(this) 会创建和初始化 UI 界面，并将其添加到当前 QWidget 的布局中
    //就可以将自己的逻辑与 UI 组件进行交互，并使用信号槽等机制来处理 UI 事件。

    //设置图片
    QImage image("D:/QT/1.00/SCU-QTimage/SCU-QTimage/res/SCU-QTimage.svg");

    QPixmap pixmap = QPixmap::fromImage(image.scaled(ui->label_Pic->size(), Qt::KeepAspectRatio));
    //使用 QImage 打开图片后，使用 scaled() 方法对 QImage 进行缩放处理，需要将其转化为 QPixmap 类型并设置为 QLabel 控件的图片。

    //Qt::KeepAspectRatio是Qt图像处理模块中的一个常量，用于指定图像的缩放策略。该常量表示在缩放图像时，保持图像长宽比不变，不会出现图像被拉伸或压缩的情况。
    //使用该常量时，可以将其作为QPixmap::scaled()或QImage::scaled()方法的第二个参数传递
    ui->label_Pic->setPixmap(pixmap);


    //设置字
    QFont font ("Microsoft YaHei", 16, 75); //声明并初始化了一个 QFont 变量，该变量使用微软雅黑字体、16 点的字号和粗体效果
    ui->label_Text->setText("SCU-QTimage"); //使用 setText() 函数将指定的文本字符串设置为 QLabel 控件的文本
    ui->label_Text->setFont(font);  //使用 setFont() 函数将该字体应用于 QLabel 控件。
    ui->label_Text->setAlignment(Qt::AlignHCenter);   //使用 setAlignment() 函数将 QLabel 控件文本的对齐方式设置为    水平居中
    ui->label_Text->setStyleSheet("color:#12BCFB;");  // 使用 setStyleSheet() 函数设置 QLabel 控件文本的颜色为   蓝绿色
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

//三个button
void AboutDialog::on_pushButton_clicked()
{
    QProcess::startDetached("explorer https://github.com/Agonie2004/SCU-QTimage");
}

void AboutDialog::on_pushButton_2_clicked()
{
    QProcess::startDetached("explorer https://cs.scu.edu.cn/");
    //::startDetached("D://QT//1.00//qtimage-main//qtimage-main//res//member.png");
}


void AboutDialog::on_pushButton_3_clicked()
{
    QProcess::startDetached("explorer https://github.com/Agonie2004/SCU-QTimage");
}
