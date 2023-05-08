#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
//QDebug在Qt库中是一个日志记录工具
//可以使用 qDebug() 方法将调试消息记录到控制台中。
#include <QGraphicsPixmapItem> 
//用于在QGraphicsScene中显示位图（Pixmap）图像。
//该类继承自QGraphicsItem，可以通过该类来创建一个用于显示图片的图形项，并将其添加到场景中

//初始化
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this); //初始化UI界面

    //初始化
    leftScene = new QGraphicsScene;            //创建QGraphicsScene对象
                                               //这是QT图像视图框架李用于管理图形元素的场景
    leftPixmapItem = new QGraphicsPixmapItem();//创建QGraphicsPixmapItem，用于显示图片

    rightScene = new QGraphicsScene;
    rightPixmapItem = new QGraphicsPixmapItem();

    //初始化
    Pixel = new QLabel;   //显示鼠标位置像素信息
    size = new QLabel;    //显示图像大小
    info = nullptr;
    ConstImage="";       //存储图像路径
    flag=false;          //用于照片是否保存的确认

    //初始化界面m
    leftScene->setBackgroundBrush(QColor::fromRgb(224,224,224));  //设置leftScene的背景颜色为灰色
    ui->leftGraphicsView->setScene(leftScene);                      //设置到左边视图中
    rightScene->setBackgroundBrush(QColor::fromRgb(224,224,224));   //设置rightScene的背景颜色为灰色
    ui->rightGraphicsView->setScene(rightScene);                    //设置到右边视图中

    //初始化底部statusBar
    ui->statusBar->addPermanentWidget(size);                       //将图片大小放到底部状态栏
    ui->statusBar->addPermanentWidget(Pixel);                      //将鼠标状态放到底部状态栏

    createToolBar();                                               //创造工具栏
    setActionStatus(false);                                      //设置动作状态是false，用于调用工具栏
    setWindowTitle("SCU-QTimage");                                 //设置窗口标题

}

//添加bar
void MainWindow::createToolBar()
{
    //toolBar_File 文件工具栏
    ui->toolBar_File->addAction(ui->doOpen);    //Action 打开
    ui->toolBar_File->addAction(ui->doSave);      //Action 保存
    ui->toolBar_File->addSeparator();            //分隔符
    ui->toolBar_File->addAction(ui->doClose);   //Action 关闭
    ui->toolBar_File->addAction(ui->doRestore);   //Action 恢复

    //toolBar_Edit  编辑工具栏
    ui->toolBar_Edit->addAction(ui->do_adjust);   //Action 左右调整
    ui->toolBar_Edit->addAction(ui->do_adjust_left);   //ACtion 左调整
    ui->toolBar_Edit->addAction(ui->do_adjust_right);  //Action 右调整
    ui->toolBar_Edit->addSeparator();
    ui->toolBar_Edit->addAction(ui->doRotate);        //Action 旋转
    ui->toolBar_Edit->addAction(ui->doRotate_left);   //Action 向左旋转 90
    ui->toolBar_Edit->addAction(ui->doRotate_right);  //Action 向右旋转 90
    ui->toolBar_Edit->addSeparator();
    ui->toolBar_Edit->addAction(ui->doHorizontal);     //Action 水平反转
    ui->toolBar_Edit->addAction(ui->doVertical);       //Action 竖直翻转
    //toolBar_Special 特效工具栏
    ui->toolBar_Change->addAction(ui->doZoom);         //Action 缩放
    ui->toolBar_Change->addAction(ui->doBrightness);   //Action  亮度调整
    ui->toolBar_Change->addSeparator();
    ui->toolBar_Change->addAction(ui->doWarm);            //ACtion 暖色调
    ui->toolBar_Change->addAction(ui->doCool);           //Action  暖色调
    //ui->toolBar_Change->addSeparator();
    ui->toolBar_Special->addAction(ui->doGrayscale);     //Action 灰度处理
    //ui->toolBar_Special->addSeparator();
    ui->toolBar_Special->addAction(ui->doSimple);        //Action 简单模糊
    ui->toolBar_Special->addAction(ui->doGauss);         //Action 高斯模糊
    //ui->toolBar_Special->addSeparator();
   // ui->toolBar_Cal->addSeparator();

    //toolBar_About 关于工具栏
    ui->toolBar_About->addAction(ui->doAbout);  //Action 关于
    ui->toolBar_About->addSeparator();
    ui->toolBar_About->addAction(ui->doExit);  //Action 退出
}


//关闭窗口时
MainWindow::~MainWindow()
{


    delete ui;

    if (leftScene)
    {
        delete leftScene;
        leftScene = nullptr;
    }

    if (size)
    {
        delete size;
        size = nullptr;
    }

    if (rightScene)
    {
        delete rightScene;
        rightScene = nullptr;
    }
}

//在程序关闭时显示确认消息框
void MainWindow::closeEvent(QCloseEvent *event){
    //如果更改了图像，但没有保存
    if(flag){
        //QMessageBox：：question（）显示一个提示框，询问用户“尚未保存，是否保存”。
        //提示框提供了Yes和NO两个按钮。如果选yes，返回QMessageBox：：Yes，No则同理
        //QMessageBox：：question（QWidget *parent，const QString &title，const QString &text，QMessageBox::StandardButtons buttons = QMessageBox::Ok, QMessageBox::StandardButton defaultButton = QMessageBox::NoButton）
        //StandardButtons，消息框按钮组合
        //defaultButton，默认选择的按钮
        //tr：精选字符串翻译  QString tr（const char *sourceText，const char * comment = nullptr）
        //如果设置中文环境，则返回相同的中文字符串，如果设置英文环境，则返回对应的英文翻译字符串
        if(QMessageBox::Yes==QMessageBox::question(this,tr("尚未保存"),tr("是否保存？"),QMessageBox::Yes | QMessageBox::No,QMessageBox::No)){
            on_doSave_triggered();
        }
    }
    //显示Exit消息框，询问是否确认退出
    if(QMessageBox::Yes==QMessageBox::question(this,tr("退出"),tr("是否退出？"),QMessageBox::Yes | QMessageBox::No,QMessageBox::No)){
        event->accept(); //关闭事件，程序退出
    }else {
        event->ignore();//忽略关闭事件，程序不退出
    }

}

//未加载图片，将图片处理按钮设为不可用
void MainWindow::setActionStatus(bool status)  //初始化时， status = false
{
    //ui->setEnabled（status） 启用或禁用UI界面中的部件
    //status 如果为true，用户可以与组件交互
    //status 如果为false，用户无法与组件交互，部件呈现禁用状态，如按钮变灰
    ui->doCool->setEnabled(status);
    ui->doWarm->setEnabled(status);
    ui->doGauss->setEnabled(status);
    ui->doRotate->setEnabled(status);
    ui->doSimple->setEnabled(status);
    ui->doRestore->setEnabled(status);
    ui->doSave->setEnabled(status);
    ui->doSave_As->setEnabled(status);
    ui->do_adjust->setEnabled(status);
    ui->doVertical->setEnabled(status);
    ui->doGrayscale->setEnabled(status);
    ui->doHorizontal->setEnabled(status);
    ui->do_adjust_left->setEnabled(status);
    ui->do_adjust_right->setEnabled(status);
    ui->doBrightness->setEnabled(status);
    ui->doZoom->setEnabled(status);
    ui->doClose->setEnabled(status);
    ui->doRotate_left->setEnabled(status);
    ui->doRotate_right->setEnabled(status);
}


/******************************************************************************
 *                              获得当前用户的桌面目录
 *****************************************************************************/
QString MainWindow::getUserPath()
{
    //QStandardPaths::writableLocation(StandardLocation type)函数获取可写的文件夹位置
    //QStandardPaths::DesktopLocation指定获取桌面文件夹位置
    QString userPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    return userPath;
}

/**********************************************************************************
 *                                    打开
 * ********************************************************************************/
void MainWindow::on_doOpen_triggered()
{
    //如果之前未曾打开图像,则调用getUserPath()函数获取打开路径。
    //如果已有路径,则使用上次的路径ConstImage
    if(flag){
        if(QMessageBox::Yes==QMessageBox::question(this,tr("尚未保存"),tr("是否返回操作？"),QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes)){
            return;
        }
    }
    /*
     *TODO:第一次打开桌面选择,第二次打开上次目录
     */
    //如果还没有保存过图像的路径
    if(ConstImage==""){
        ConstImage=getUserPath();//获得图像路径
    }
    //QFileDialog::getOpenFileName()函数打开图像选择框,让用户选择要打开的图像
    //第一个参数 - 父窗口
    //第二个参数 - 选择框标题
    //第三个参数 - ConstImage 默认打开的路径
    //第四个参数 - 过滤器 - 指定用户可以选择的文件类型，这里可选择照片格式和所有文件
    //用户在选择框中选择一个图像文件后,该函数将返回选择的图像文件的完整路径,存储在imagePath字符串中
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open image"), ConstImage,
                                                     tr("All Images (*.bpm *.jpg *.jpeg *.png *.tif *.pcx *.tga *.svg *.ico);;"
                                                        "All Files (*);;"
                                                        "Image BPM (*.bpm);;"
                                                        "Image JPG (*.jpg);;"
                                                        "Image JPEG (*.jpeg);;"
                                                        "Image PNG (*.png);;"));

    //将选择的图像路径imagePath存储在全局变量ConstImage中,作为下次打开图像的默认路径
    ConstImage=imagePath;
    //检查图像路径是否为空,如果为空则结束函数
    if (!imagePath.isEmpty())//首先地址
    {
        QFile file(imagePath);
        //创建QFile对象打开选择的图像文件
        //QIODevice::ReadOnly打开选择的图像文件imagePath，如果无法打开，则返回false
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr(WINDOW_ERROR),
                                  tr("不能打开这个文件！"));
            return;
        }

        //将之前的图片清除掉，清除左右视图并重置状态
        cleanImage();

        // 创建QFileInfo对象，获得选择的图像信息，如文件名，大小等
        info = new QFileInfo(imagePath);

        //左框显示图片
        QPixmap leftPixmap(imagePath);//创建一个QPixmap对象leftPixmap,用于访问imagePath指定的图像文件
        leftPixmapItem = leftScene->addPixmap(leftPixmap);//将leftPixmap添加到左图形视图leftScene中
        leftScene->setSceneRect(QRectF(leftPixmap.rect()));//更新左图形视图leftScene的场景矩形setSceneRect(),使其刚好包围住图像的大小
        //右框显示图片
        QPixmap rightPixmap(imagePath);
        rightPixmapItem = rightScene->addPixmap(rightPixmap);
        rightScene->setSceneRect(QRectF(rightPixmap.rect()));

        //调整使得图片适应边框
        on_do_adjust_triggered();

        //更改软件标题
        this->setWindowTitle(info->fileName() + " - SCU-QTimage");

        //设置操作可用
        setActionStatus(true);

        //statusBar更新信息
        double size_h=info->size()*1.0/1024;//获取图片的大小，单位kb
        QString size_type=" KB";
        //进制转化，将kb转化为MB
        if(size_h>=1024){
            size_h/=1024;
            size_type=" MB";
        }
        size->setText(QString::number(size_h, 'f', 2)+size_type); //将图像大小设置在状态栏中，保存类型为float的保留两位形式
        Pixel->setText(QString::number(leftPixmapItem->pixmap().width())
                       + " x " + QString::number(leftPixmapItem->pixmap().height()));  //设置图片的宽度和高度

        flag=false;//表示图片已保存
    }

}
/**********************************************************************************
 *                                  清理图片
 * ********************************************************************************/
void MainWindow::cleanImage()
{
    //左边框清理
    leftScene->clear();
    //重置变换矩阵函数：
    //1. 取消先前图像的所有变换,为显示新图像做准备。
    //2. 恢复默认视图,以使新操作或变换从初始状态开始。
    ui->leftGraphicsView->resetTransform();
    //右边
    rightScene->clear();
    ui->rightGraphicsView->resetTransform();

    //更新statusBar->通过删除原对象，重新new一个新对象来完成
    if (size)
    {
        delete size; //删除size
        size = new QLabel;
        //addPermanentWidget：向QStatusBar(状态栏)中添加一个永久部件
        //void QStatusBar::addPermanentWidget(QWidget *widget, int stretch = 0)
        //- widget:要添加的部件,如QLabel、进度条等。
        //- stretch:该部件占据的默认空间,可对齐多个部件。
        //这个函数将向状态栏的右边添加给定的widget部件。不同于临时消息,这个部件将一直显示在状态栏上,直到被removeWidget()函数移除。
        ui->statusBar->addPermanentWidget(size);
    }
    if(Pixel){
        delete Pixel;
        Pixel = new QLabel;
        ui->statusBar->addPermanentWidget(Pixel);
    }
    //还原标题
    this->setWindowTitle(WINDOW_TITLE); //mainwindow.h的宏定义：WINDOW_TITLE = “SCU-QTimage”

    //控件设为不可用
    setActionStatus(false);
}

/**********************************************************************************
 *                                    关闭
 * ********************************************************************************/
void MainWindow::on_doClose_triggered()
{
    if(flag){
        if(QMessageBox::Yes==QMessageBox::question(this,tr("尚未保存"),tr("是否返回操作再关闭？"),QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes)){
            return;
        }
    }
    //直接清理图片
    cleanImage();  //下一个函数
    flag=false;
    //更新标志，以待下一次使用
}


/**********************************************************************************
 *                                     保存
 * ********************************************************************************/
void MainWindow::on_doSave_triggered()
{
    //首先将右边图与本地图片进行替换
    //将右边图像保存到ConstImage路径下的地址中（即替换掉原图片）
    rightPixmapItem->pixmap().save(ConstImage);

    //清楚左边框图片
    leftScene->clear();
    ui->leftGraphicsView->resetTransform();

    //更新底部statusBar
    if (size)
    {
        delete size;
        size = new QLabel;
        ui->statusBar->addPermanentWidget(size);
    }
    if(Pixel){
        delete Pixel;
        Pixel = new QLabel;
        ui->statusBar->addPermanentWidget(Pixel);
    }

    //重新获取图片信息
    // 创建QFileInfo对象，获得选择的图像信息，如文件名，大小等
    info = new QFileInfo(ConstImage);

    //左框重新显示图片
    QPixmap leftPixmap(ConstImage);
    leftPixmapItem = leftScene->addPixmap(leftPixmap);
    leftScene->setSceneRect(QRectF(leftPixmap.rect()));

    //更新底部statusBar
    double size_h=info->size()*1.0/1024;
    QString size_type=" KB";
    if(size_h>=1024){
        size_h/=1024;
        size_type=" MB";
    }
    size->setText(QString::number(size_h, 'f', 2)+size_type);
    Pixel->setText(QString::number(leftPixmapItem->pixmap().width())
                   + " x " + QString::number(leftPixmapItem->pixmap().height()));

    //仅调整左边图片适应窗口
    on_do_adjust_left_triggered();
    flag=false;
}

/**********************************************************************************
 *                                    另存为
 * ********************************************************************************/
void MainWindow::on_doSave_As_triggered()
{

    //直接用原始图片作为地址和名字
    //QFileDialog::getSaveFileName(this, tr("Save image"), ConstImage,
    //- 以this作为父窗口打开文件对话框
    //- 设置对话框标题为tr("Save image"),即"保存图像"
    //- 初始文件路径为ConstImage
    QString newPath = QFileDialog::getSaveFileName(this, tr("Save image"), ConstImage,
                                                   tr("All files (*);;"
                                                      "Image BPM (*.bpm);;"
                                                      "Image JPG (*.jpg);;"
                                                      "Image JPEG (*.jpeg);;"
                                                      "Image PNG (*.png);;"
                                                      "Image SVG (*.svg);;"
                                                      "Image ICO (*.ico);;"
                                                      "Image TIF (*.tif);;"
                                                      "Image PCX (*.pcx);;"
                                                      "Image TGA (*.tga);;"));

    //检测是否能够保存 逻辑同打开
    if (!newPath.isEmpty()) {
        QFile file(newPath);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, tr(WINDOW_ERROR), tr("不能保存这个文件！"));
            return;
        }
        rightPixmapItem->pixmap().save(newPath);
        flag=false;
    }
}

/**********************************************************************************
 *                                    退出
 * ********************************************************************************/
void MainWindow::on_doExit_triggered()
{
    //检查是否更改
    if(flag){
        if(QMessageBox::Yes==QMessageBox::question(this,tr("尚未保存"),tr("是否返回操作再退出？"),QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes)){
            return;
        }
    }
    cleanImage();
    qApp->quit();
}


/**********************************************************************************
 *                                    更新右边图片
 * ********************************************************************************/
void MainWindow::updateRightImage(QPixmap &pixmap)
{
    //刷新右边图片
    rightPixmapItem->setPixmap(pixmap);
    //这段代码的作用是:将右侧QGraphicsScene的场景范围设置为左边图像的大小。
    //具体分析:
    //rightScene是一个QGraphicsScene,用于管理右侧图形视图的项目与显示。
    //setSceneRect()是QGraphicsScene提供的函数,用于设置场景的范围矩形。
    //QRectF(pixmap.rect())构造一个according to QRectF,其范围匹配左边图片的大小。pixmap.rect()获取左边图片的范围
    rightScene->setSceneRect(QRectF(pixmap.rect()));
}

/**********************************************************************************
 *                                 恢复右边
 * ********************************************************************************/
void MainWindow::on_doRestore_triggered()
{
    //获取左侧图片
    QPixmap leftImage = leftPixmapItem->pixmap();

    //用左侧图片更新右侧
    updateRightImage(leftImage);
    //调整图像自适应
    on_do_adjust_right_triggered();
    flag=false;  //按钮失效
}


/**********************************************************************************
 *                                    灰度
 * ********************************************************************************/
void MainWindow::on_doGrayscale_triggered()
{
    //首先获取原先的rightImage
    QPixmap rightImage = rightPixmapItem->pixmap();

    //效果处理 灰度图片 调用Algorithm::GreyScale()
    QImage newImage = Algorithm::GreyScale(rightImage.toImage());//Algorithm.cpp

    //将QImage转为QPixmap
    rightImage.convertFromImage(newImage);

    //更新图片
    updateRightImage(rightImage);
    flag=true;
}


/**********************************************************************************
 *                                    冷
 * ********************************************************************************/
void MainWindow::on_doCool_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap(); //创建一个新的QPixmap对象

    //效果处理 色素变幻 调用Algorithm::Cool()
    QImage newImage = Algorithm::Cool(30, rightImage.toImage());

    rightImage.convertFromImage(newImage);
    updateRightImage(rightImage);
    flag=true;
}

/**********************************************************************************
 *                                    温
 * ********************************************************************************/
void MainWindow::on_doWarm_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();

    //效果处理 色素变幻 调用Algorithm::Warm()
    QImage newImage = Algorithm::Warm(30, rightImage.toImage());

    rightImage.convertFromImage(newImage);
    updateRightImage(rightImage);
    flag=true;
}



/**********************************************************************************
 *                                    简单平滑
 * ********************************************************************************/
void MainWindow::on_doSimple_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();

    //效果处理 像素点处理 调用Algorithm::SimpleSmooth()
    QImage newImage = Algorithm::SimpleSmooth(rightImage.toImage());

    rightImage.convertFromImage(newImage);
    updateRightImage(rightImage);
    flag=true;
}
/**********************************************************************************
 *                                    高斯
 * ********************************************************************************/
void MainWindow::on_doGauss_triggered()
{
    //输入框
    GaussianBlurDialog dialog;
    //信号处理
    connect(&dialog, SIGNAL(sendData(int, double)), this,
            SLOT(receiveGaussValue(int, double)));
    //阻塞对话框
    dialog.exec();
}
//高斯处理
void MainWindow::receiveGaussValue(int radius, double sigma)
{
    //new对象
    GaussBlur *blur = new GaussBlur(radius, sigma);

    QPixmap rightImage = rightPixmapItem->pixmap();

    //QPixmap转化为image之后进调用BlurImage()进行处理
    QImage newImage = blur->StartGauss(rightImage.toImage());

    rightImage.convertFromImage(newImage);
    updateRightImage(rightImage);
    flag=true;
}


/**********************************************************************************
 *                                    缩放
 * ********************************************************************************/
void MainWindow::on_doZoom_triggered()
{
    //快速创建对话框
    bool isOK;
    int LocalValue = QInputDialog::getInt(this, tr("缩放"), "请输入缩放值(10-1000)(%)",100,10,1000,10,&isOK);
    if (isOK)
    {
        if (LocalValue != 100)
        {
            QPixmap rightImage = rightPixmapItem->pixmap();

            int cur_width = rightImage.width();
            int cur_height = rightImage.height();

            //效果处理 缩放 调用自带缩放
            QPixmap newPixmap = rightImage.scaled(cur_width*LocalValue/100, cur_height*LocalValue/100);

            updateRightImage(newPixmap);
            flag=true;
        }
        else
        {
            return;
        }
    }
}

/**********************************************************************************
 *                                    水平翻转
 * ********************************************************************************/
void MainWindow::on_doHorizontal_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();

    //效果处理 水平翻转 调用Algorithm::Horizontal()
    QImage newImage = Algorithm::Horizontal(rightImage.toImage());

    rightImage.convertFromImage(newImage);
    updateRightImage(rightImage);
    flag=true;
}

/**********************************************************************************
 *                                    垂直翻转
 * ********************************************************************************/
void MainWindow::on_doVertical_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();

    //效果处理 垂直翻转 调用Algorithm::Vertical()
    QImage newImage = Algorithm::Vertical(rightImage.toImage());

    rightImage.convertFromImage(newImage);
    updateRightImage(rightImage);
    flag=true;
}



/**********************************************************************************
 *                                    亮度
 * ********************************************************************************/
void MainWindow::on_doBrightness_triggered()
{
    bool isOK;
    int delta = QInputDialog::getInt(this,tr("亮度"),"请输入参数(+/-)",0,-1000,1000,10,&isOK);
    if (isOK)
    {
        if (delta != 100)
        {
            QPixmap rightImage = rightPixmapItem->pixmap();

            //效果处理 调整亮度 调用Algorithm::Brightness()
            QImage newImage = Algorithm::Brightness(delta, rightImage.toImage());

            rightImage.convertFromImage(newImage);
            updateRightImage(rightImage);
            flag=true;
        }
        else
        {
            return;
        }
    }

}


/**********************************************************************************
 *                                    关于
 * ********************************************************************************/
void MainWindow::on_doAbout_triggered()
{
    AboutDialog dialog; //创建AboutDialog类的对象
    dialog.exec();
}



/**********************************************************************************
 *                                    旋转
 * ********************************************************************************/
void MainWindow::on_doRotate_triggered()
{
    bool isOK;
    int LocalValue = QInputDialog::getInt(this, tr("旋转"), "请输入要旋转的角度（正数向右，负数向左）",0,-360,360,10,&isOK);
    if (isOK)
    {
        if (LocalValue != 0)
        {
            QPixmap rightImage = rightPixmapItem->pixmap();
            QImage *imgRotate = new QImage;
            QMatrix matrix;
            matrix.rotate(LocalValue);
            *imgRotate = rightImage.toImage().transformed(matrix);
            QPixmap newPixmap;
            newPixmap = QPixmap::fromImage(*imgRotate);
            updateRightImage(newPixmap);
            flag=true;
        }
        else
        {
            return;
        }
    }
}

void MainWindow::on_doRotate_left_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage *imgRotate = new QImage;
    QMatrix matrix;
    matrix.rotate(-90);
    *imgRotate = rightImage.toImage().transformed(matrix);
    QPixmap newPixmap;
    newPixmap = QPixmap::fromImage(*imgRotate);
    updateRightImage(newPixmap);
    flag=true;
}

void MainWindow::on_doRotate_right_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage *imgRotate = new QImage;
    QMatrix matrix;
    matrix.rotate(90);
    *imgRotate = rightImage.toImage().transformed(matrix);
    QPixmap newPixmap;
    newPixmap = QPixmap::fromImage(*imgRotate);
    updateRightImage(newPixmap);
    flag=true;
}

/**********************************************************************************
 *                                    调整图片适应界面
 * ********************************************************************************/
void MainWindow::on_do_adjust_triggered()
{
    on_do_adjust_left_triggered();
    on_do_adjust_right_triggered();
}

/*****************************************************************************
 *                            调整左边图片适应
 * **************************************************************************/
void MainWindow::on_do_adjust_left_triggered()
{
    //恢复
    ui->leftGraphicsView->resetTransform();

    //左图
    int height = leftPixmapItem->pixmap().height();
    int width = leftPixmapItem->pixmap().width();
    int max_height = ui->leftGraphicsView->height(); //左操作框的界面高度
    int max_width = ui->leftGraphicsView->width();   //左操作框的截面宽度

    //计算
    int pic_size = qMax(width,height);
    int max_size = qMin(max_width,max_height)-5;
    double val = (max_size*1.0)/pic_size;

    ui->leftGraphicsView->scale(val,val);
}
/*****************************************************************************
 *                            调整右边图片适应
 * **************************************************************************/
void MainWindow::on_do_adjust_right_triggered()
{
    //恢复
    ui->rightGraphicsView->resetTransform();

    // 右图
    int height = rightPixmapItem->pixmap().height();
    int width = rightPixmapItem->pixmap().width();
    int max_height = ui->rightGraphicsView->height(); //右操作框的界面高度
    int max_width = ui->rightGraphicsView->width();  //右操作框的截面宽度

    //计算
    int pic_size = qMin(width,height);     //取最小值
    int max_size = qMin(max_width,max_height)-5;  //取最小值 - 5 ，防止上溢

    double val = (max_size*1.0)/pic_size;

    //更新
    ui->rightGraphicsView->scale(val,val);
}

/*****************************************************************************
 *                               简单平滑处理
 * kernel矩阵决定计算中相邻像素的影响程度
 * 然后使用滤波器进行计算
 * eg:
 *R = 20 102 99
 *    150 200 77
 *    170 210 105
 *Kenel = 0 2 0
 *        2 5 2
 *        0 2 0
 * r = ( (102*2) + (150*2) + (200*5) + (77*2) + (210*2) ) / (2+2+5+2+2) = 159
 * **************************************************************************/
QImage Algorithm::SimpleSmooth(const QImage &origin)
{
    QImage *newImage = new QImage(origin);

    int kernel[5][5] = {
        {0,0,1,0,0},
        {0,1,3,1,0},
        {1,3,7,3,1},
        {0,1,3,1,0},
        {0,0,1,0,0}
    };
    int startKernel=2;
    int sumKernel=27;
    int r,g,b;
    QColor color;

    //起始点第3个像素点 结束点是倒数第3个像素点
    for(int x=startKernel; x<newImage->width()-startKernel; ++x)
    {
        for (int y=startKernel; y<newImage->height()-startKernel; ++y)
        {
            r = g = b = 0;   //r，g，b的值默认赋值为0
            for (int i=-startKernel; i<=startKernel; ++i)
            {
                for (int j=-startKernel; j<=startKernel; ++j)
                {
                    color = QColor(origin.pixel(x+i,y+j));
                    r += color.red()*kernel[startKernel+i][startKernel+j];
                    g += color.green()*kernel[startKernel+i][startKernel+j];
                    b += color.blue()*kernel[startKernel+i][startKernel+j];
                }
            }
            r = qBound(0, r/sumKernel, 255);
            g = qBound(0, g/sumKernel, 255);
            b = qBound(0, b/sumKernel, 255);

            newImage->setPixel(x,y,qRgb(r,g,b));

        }
    }
    return *newImage;
}
