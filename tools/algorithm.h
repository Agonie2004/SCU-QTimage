#ifndef TOOLS_H
#define TOOLS_H

#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QPainter>
#include <QtMath>
#include "gaussblur.h"
//算法部分
namespace  Algorithm {
QImage GreyScale(QImage origin);  //灰度处理
QImage Warm(int delta, QImage origin);//暖色调
QImage Cool(int delta, QImage origin);//冷色调
QImage Brightness(int delta, QImage origin);//亮度
QImage Horizontal(const QImage &origin);//水平翻转
QImage Vertical(const QImage &origin);//垂直翻转
QImage SimpleSmooth(const QImage &origin);//简单平滑处理
QImage GaussianSmoothing(const QImage &origin, int radius, double sigma);//高斯平滑

}

#endif // TOOLS_H
