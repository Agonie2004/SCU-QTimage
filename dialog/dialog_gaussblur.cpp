#include "dialog_gaussblur.h"
#include "ui_gaussblurdialog.h"

// 这两行代码包含了 GaussianBlur Dialog 类所需的头文件
//其中 dialog_gaussblur.h 包含类的声明
//ui_gaussblurdialog.h 包含 Qt Designer 生成的对话框窗口部件类的声明。

GaussianBlurDialog::GaussianBlurDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GaussianBlurDialog)
{
    ui->setupUi(this);
}

GaussianBlurDialog::~GaussianBlurDialog()
{
    delete ui;
}

//信号处理
void GaussianBlurDialog::on_buttonOK_accepted()
{
    emit sendData(ui->radiusSpinBox->value(), ui->sigmaSpinBox->value());
}
