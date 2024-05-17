#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QWidget>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
   // explicit MyPushButton(QWidget *parent = nullptr);
    //构造函数 参数1 正常显示的图片 ，    参数2 按下后显示的图片路径
    MyPushButton(QString normalImg , QString pressImag = "");
    //成员属性 保存用户传入的默认显示路径 以及按下后显示的图片路径
    QString normalImgPath;
    QString pressImgPath;

    //弹跳特效
    void zoom1();//向下跳
    void zoom2();//向上跳

    //重写按钮 按下 和 释放 事件
    void mousePressEvent(QMouseEvent*)override;

    void mouseReleaseEvent(QMouseEvent*)override;

signals:
};

#endif // MYPUSHBUTTON_H
