#ifndef GAUSSBLUR_H
#define GAUSSBLUR_H
//https://zhuanlan.zhihu.com/p/358910882  高斯模糊介绍
/*
 * 算法参考:
 * http://www.ruanyifeng.com/blog/2012/11/gaussian_blur.html
 */
#include <vector>

#include "qcolor.h"
#include "qimage.h"

using std::vector;

class GaussBlur
{

public:
    GaussBlur(int blurRadius, double sigma); //blurRadius代表模糊半径 ，sigma代表标准差
    ~GaussBlur();
    QImage StartGauss(const QImage& in);
    //构造函数GaussBlur()会根据这两个参数计算出高斯矩阵gs_matrix,用于后续的模糊运算。

private:
    //用于存放高斯模糊所需的矩阵
    float *gs_matrix;
    //矩阵大小和一半长
    int matrixSize,halfMatrixSize;
    //两个参数
    int Radius;
    double  Sigma;
    //高斯公式
    double GaussFormula(double x);
    //获取坐标
    int GetIndex(int x, int length);
    //计算矩阵
    void GetMatrix();
};

#endif // GAUSSBLUR_H
