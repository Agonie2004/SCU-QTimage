## QPixmap类

QPixmap类提供了许多功能函数,主要包括:- **加载图像**

```
cpp
bool load(const QString &fileName, const char *format = nullptr, Qt::ImageConversionFlags flags = Qt::AutoColor);
bool loadFromData(const uchar *buf, uint len, const char *format = nullptr, Qt::ImageConversionFlags flags = Qt::AutoColor);
```

从文件或内存缓冲加载图像,支持各种格式。- **获取信息**

```
cpp
int width() const; 
int height() const;
QSize size() const;
QPoint offset() const; 
QString format() const;
```

获取图像宽、高、大小、偏移、格式等信息。- **操作图像**

```
cpp
QPixmap scaled(int width, int height, Qt::AspectRatioMode mode = Qt::IgnoreAspectRatio, 
                 Qt::TransformationMode transformMode = Qt::FastTransformation) const;
QPixmap scaledToWidth(int width, Qt::TransformationMode mode = Qt::FastTransformation) const;
QPixmap scaledToHeight(int height, Qt::TransformationMode mode = Qt::FastTransformation) const;  
QPixmap transformed(const QMatrix &matrix, Qt::TransformationMode mode = Qt::FastTransformation) const;
QPixmap rotated(int degrees, Qt::BGMode bgMode, QVariant bgColor = QVariant()) const;
```

实现图像的缩放、旋转、扭曲等操作。- **绘制与填充**

```
cpp
void fill(const QColor &color = Qt::white); 
void fill(const QPaintDevice *device, const QPoint &ofs);
```

使用颜色或设备内容填充图像。- **保存图像**

```
cpp
bool save(const QString &fileName, const char *format = nullptr, int quality = -1) const;
```

保存图像到文件,可以指定格式与质量。- 等等还有转换格式、创建镜像、设置高清屏幕支持等更多功能。



## QFileInfo类

QFileInfo类提供文件信息的获取与操作。通过它,我们可以轻松获取文件路径、大小、权限、类型、最后修改时间等信息。主要功能包括:- 获取文件基本信息:

```
cpp
QString filePath() const; 
QString absoluteFilePath() const;
QString baseName() const;
QString suffix() const;
QDateTime lastModified() const;
qint64 size() const; 
bool isFile() const;
bool isDir() const;
```

\- 获取文件路径信息:

```
cpp
QString dir() const;
QString dir(Dir dirOption) const;
QString canonicalPath() const;
QString path() const; 
QString absolutePath() const;
```

\- 获取文件权限与类型:

```
cpp
bool permission(Permissions permissions) const;
QFile::Permissions permissions() const;
```

\- 文件操作:

```
cpp 
bool copy(const QString &newName);
bool rename(const QString &newName);
bool remove();
```

\- 等等所以,通过QFileInfo,我们可以方便地在程序中获取文件信息,并进行基本的文件操作。这为处理文件提供了基础的功能支持。



## QRectF类

QRectF类是QT中用于表示浮点数精度的矩形区域的类。与QRect不同,QRectF使用qreal(双精度浮点数)存储矩形的坐标与大小,可以提供更高的精度。主要功能包括:- 构造函数:

```
cpp
QRectF();  // 默认构造一个null矩形 
QRectF(const QPointF &topLeft, const QPointF &bottomRight);
QRectF(qreal x, qreal y, qreal width, qreal height);
```

\- 获取信息:

```
cpp
qreal x() const; 
qreal y() const;
qreal width() const;
qreal height() const;
QSizeF  size() const;
QPointF topLeft() const;
QPointF bottomRight() const;
QPointF center() const;
```

\- 操作矩形:

```
cpp
void setLeft(qreal x);
void setRight(qreal x); 
void setTop(qreal y);
void setBottom(qreal y);
void setX(qreal x);
void setY(qreal y); 
void setWidth(qreal width); 
void setHeight(qreal height);
```

\- 关系判断:

```
cpp
bool contains(const QPointF &point) const;
bool intersects(const QRectF &rectangle) const; 
```

\- 等等所以,QRectF提供了一组方便操作浮点数矩形区域的工具,使用它可以简化我们自己计算浮点数坐标所带来的精度问题。它常常用于QT的矢量图形与 imaging等高精度区域处理



## QDialog类

QDialog是QT中提供的对话框基类。通过它,我们可以轻松创建各种复杂的对话框。QDialog主要功能包括:- 构造函数:

```
cpp
QDialog();
QDialog(QWidget *parent);
```

\- 设置对话框标题、图标等:

```
cpp
void setWindowTitle(const QString &title);
void setWindowIcon(const QIcon &icon);
```

\- 添加标准按钮:

```
cpp
void addButton(QPushButton *button);
QPushButton *addButton(const QString &text, const QDialogButtonBox::StandardButton &button);
QDialogButtonBox *createButton(); 
```

\- 设置布局:

```
cpp
void setLayout(QLayout *layout);
```

\- 调整大小:

```
cpp 
void adjustSize();
void setFixedSize(const QSize &size);
void setMinimumSize(const QSize &size); 
void setMaximumSize(const QSize &size);
```

 \- 事件处理:

```
cpp
void accept();    // 相当于点击确定按钮
void reject();    // 相当于点击取消按钮
```

\- 等等。QDialog让我们可以方便地创建和管理对话框。我们可以设置标题、添加各种按钮、使用任意布局放置各控件、处理用户交互事件等。这为设计复杂的交互窗口提供了强有力的支持。





## QGraphicsItem类

QGraphicsItem是QT中用于创建图形项的基类。通过它,我们可以实现各种自定义的图形项并添加到QGraphicsScene中显示。主要功能包括:- 构造函数:

```
cpp
QGraphicsItem(QGraphicsItem *parent = nullptr);
```

\- 设置图形项属性:

```
cpp
void setFlags(GraphicsItemFlags flags); // 设置交互标志 
void setAcceptHoverEvents(bool enabled); // 启用悬停事件
void setCacheMode(CacheMode mode);   // 设置缓存模式
void setCursor(const QCursor &cursor); // 设置鼠标光标形状
```

\- 几何函数:

```
cpp
QRectF boundingRect() const;  // 外接矩形边界
void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) = 0; // 绘制图形
```

 \- 变换:

```
cpp  
void rotate(qreal angle); // 旋转 
void scale(qreal fx, qreal fy = 1);  // 缩放
void translate(qreal dx, qreal dy); // 平移
```

\- 堆叠顺序控制:

```
cpp  
int type() const;      // 获取类型
virtual int zValue() const; // 堆叠值
```

\- 等等所以,QGraphicsItem为开发自定义图形项提供了强有力的支持。我们继承它来开发各种图形项,指定其外形、大小、位置、堆叠顺序、交互方式等,然后添加到QGraphicsScene中进行显示与交互。这是开发矢量图形应用以及各种可视化编程的基础。



## QGraphicsScene类

QGraphicsScene是一个管理QGraphicsItem的场景类。它是图形视图框架中非常重要的一环,负责协调各个图形项的显示、交互与更新。主要功能包括:- 添加/移除图形项:

```
cpp
void addItem(QGraphicsItem *item);
void removeItem(QGraphicsItem *item);
```

\- 设置场景rect:

```
cpp
void setSceneRect(const QRectF &rect); 
```

\- 堆叠顺序管理:

```
cpp
void stackBefore(QGraphicsItem *item, QGraphicsItem *sibling);
void stackAfter(QGraphicsItem *item, QGraphicsItem *sibling);  
```

\- 边界管理:

```
cpp
QList<QGraphicsItem *> items(qreal x, qreal y, qreal w, qreal h, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape, Qt::SortOrder order = Qt::DescendingOrder) const;
```

\- 更新管理:

```
cpp
virtual void update(qreal x, qreal y, qreal w, qreal h);  // 区域更新 
void invalidate(qreal x, qreal y, qreal w, qreal h, QGraphicsScene::SceneLayers layers = AllLayers); // 使区域无效
```

 \- 事件分发:

```
cpp
bool sendEvent(QGraphicsItem *item, QEvent *event);  // 发送事件
```

\- 等等QGraphicsScene作为图形项的管理中心,负责处理各图形项之间的关系,以及与视图的交互。通过它,我们可以轻松开发出高质量的矢量图形应用与各种交互式可视化界面。



## QGraphicsPixmapItem类

QGraphicsPixmapItem是一个用于显示QPixmap的QGraphicsItem。通过它,我们可以轻松地在QGraphicsScene中添加与显示图像。主要功能包括:- 构造函数:

```
cpp
QGraphicsPixmapItem(QGraphicsItem *parent = nullptr);
QGraphicsPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);
```

\- 设置/获取图片:

```
cpp
void setPixmap(const QPixmap &pixmap);
QPixmap pixmap() const;
```

\- 设置图片变换:

```
cpp
void setOffset(const QPointF &offset);   // 设置图像偏移
void setRotation(qreal angle);          // 设置图像旋转角度 
void setScale(qreal scaleX, qreal scaleY = 1);  // 设置图像缩放比例
void setShear(qreal sh, qreal sv);     // 设置图像倾斜角度   
void setTransform(const QTransform &matrix); // 设置仿射变换矩阵
```

\- 重新实现绘制函数:

```
cpp
void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
```

\- 等等QGraphicsPixmapItem继承自QGraphicsItem,专门用于添加与显示QPixmap到QGraphicsScene中。我们可以利用QGraphicsItem的各种功能,轻松实现图像的平移、旋转、缩放以及组合变换,展现复杂的图像效果。这为开发图像编辑与处理软件提供了强大的支持。



## QMessageBox类

QMessageBox是一个消息对话框类。它用于向用户显示各种消息,并提供简单的选项进行交互。主要功能包括:- 消息类型:

```
cpp
QMessageBox::Information; // 信息消息
QMessageBox::Warning;    // 警告消息
QMessageBox::Critical;   // 严重错误消息 
QMessageBox::Question;   // 询问消息
```

\- 消息对话框构造:

```
cpp
QMessageBox(QWidget *parent = nullptr);  
QMessageBox(Icon icon, const QString &title, const QString &text,
            QMessageBox::StandardButtons buttons = NoButton,
            QWidget *parent = nullptr);
```

\- 设置消息内容: 

```
cpp  
void setText(const QString &text); 
void setInformativeText(const QString &text);  // 辅助说明文字  
void setDetailedText(const QString &text);    // 详细文字  
```

\- 添加按钮:

```
cpp  
void addButton(QAbstractButton *button, QMessageBox::ButtonRole role);  
QPushButton *addButton(const QString &text,QMessageBox::ButtonRole role);
```

\- 获取用户交互结果:

```
cpp
QMessageBox::StandardButton standardButton(QAbstractButton *button) const; 
QAbstractButton *clickedButton() const; 
```

 \- 等等QMessageBox简化了向用户显示各种消息并获取简单响应的难度。我们可以方便地构造消息框,添加按钮,获取用户的选择结果进行相应处理。这在程序开发中是一个常用且十分必要的功能,QMessageBox很好地实现并封装了它。



## QImage类

QImage是一个图像类,用于加载、存储和处理图像。它提供了丰富的API来操作图像像素及其他相关属性。主要功能包括:- 构造函数:

```
cpp
QImage();    // 默认构造
QImage(const QString &fileName, const char *format = nullptr); // 从文件加载
QImage(int width, int height, Format format);  // 创建空白图像  
```

\- 图像属性:

```
cpp  
int width() const;         // 宽度
int height() const;        // 高度
bool isNull() const;       // 是否为空
Format format() const;     // 格式
```

 \- 像素访问:

```
cpp
uchar *bits();                    // 像素数据块
QRgb color(int x, int y) const;  // 获取像素颜色
void setColor(int x, int y, QRgb color);   // 设置像素颜色  
```

 \- 图像处理:

```
cpp
QImage scaled(int width, int height) const;         // 缩放
QImage mirrored(bool horizontally, bool vertically) const; // 镜像
QImage grayscale() const;                            // 灰度化       
QImage rotated(int degrees) const;                   // 旋转
```

\- 载入/保存图像:

```
cpp
bool load(const QString &fileName, const char *format = nullptr); 
bool save(const QString &fileName, const char *format = nullptr);
```

 \- 绘制图像: 

```
cpp
void fill(const QColor &color);   // 用颜色填充      
QPainter painter(this);          // 在图像上画图  
```

\- 等等。QImage提供了操作图像的全套解决方案,是开发图像处理应用的基础。理解这个类需要掌握图像格式与像素概念,并具有一定的图像处理能力。熟练使用QImage可以轻松实现各种图像特效与处理功能。



## exec（）函数

exec()函数用于执行一个事件循环,使得QT应用保持运行状态并响应各种事件。当我们构造好界面并连接各个信号/槽函数之后,需要进入事件循环使程序可以运行。否则程序会直接退出,界面无法显示与交互。exec()函数用于启动这个事件循环,会一直运行直到遇到退出事件(如关闭窗口)。常见的exec()函数包括:- QApplication::exec()启动整个应用程序的事件循环。一般放在main()函数的结尾:

```
cpp
int main(int argc, char *argv[]) 
{
    QApplication a(argc, argv);
    // 构造界面......
    // 连接信号槽...... 
    return a.exec();
}
```

\- QDialog::exec()启动QDialog的模态事件循环。函数会阻塞等待用户与对话框交互并关闭:

```
cpp
QDialog dialog;
// 构造对话框界面......
dialog.exec();
```

\- QMenu::exec()启动QMenu的弹出菜单事件循环,等待用户选择菜单项:

```
cpp 
QMenu menu;
// 添加菜单项
menu.exec(QCursor::pos());  // 以鼠标位置弹出菜单
```

\- 等等exec()函数是QT应用必不可少的一部分,理解它需要对QT的事件处理机制有比较深入的理解。掌握各个界面类的exec()函数可以帮助我们轻松构建交互式应用程序与界面。exec()让我进一步理解事件驱动程序的运行机制。但要熟练运用QT开发高质量应用,我还需要学习更广泛的知识与技能。我会努力不断学习与实践,总结经验,以完善自己的知识体系。

