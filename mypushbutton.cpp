#include "mypushbutton.h"
#include <QPropertyAnimation>

// MyPushButton::MyPushButton(QWidget *parent)
//     : QWidget{parent}
// {}

//构造函数 参数1 正常显示的图片 ，    参数2 按下后显示的图片路径
MyPushButton::MyPushButton(QString normalImg , QString pressImg){
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    QPixmap pix;
    bool ret = pix.load(normalImg);
    if(!ret){
      qDebug()<<"图片加载失败";
        return;
    }
    //设置图片固定大小
    this->setFixedSize(pix.width(),pix.height() );

    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:Opx;}");

    //设置图标
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));


}
void MyPushButton::zoom1(){//向下跳
    //创建动态对象
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //结束位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();
}
void MyPushButton::zoom2(){//向上跳
    //创建动态对象
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //结束位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();

}

//重写按钮 按下 和 释放 事件
void MyPushButton::mousePressEvent(QMouseEvent* e ){
    if(this->pressImgPath!=""){//传入图片不为空,说明需要有按下状态的图片 ，并切换
        QPixmap pix;
        bool ret = pix.load(this->pressImgPath);
        if(!ret){
            qDebug()<<"图片加载失败";
            return;
        }
        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height() );

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:Opx;}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //让父类执行其他内容
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent* e){
    if(this->pressImgPath!=""){//传入图片不为空，释放后切换成初始图片
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);
        if(!ret){
            qDebug()<<"图片加载失败";
            return;
        }
        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height() );

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:Opx;}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //让父类执行其他内容
    return QPushButton::mouseReleaseEvent(e);
}
