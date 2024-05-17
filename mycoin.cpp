#include "mycoin.h"

// MyCoin::MyCoin(QWidget *parent)
//     : QPushButton{parent}
// {
// }


//参数代表 传入的金币路径 还是银币路径
MyCoin:: MyCoin(QString btnImg){
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(!ret){
        QString str = QString("图片%1加载失败").arg(btnImg);
        qDebug()<<"图片加载失败";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:Opx;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始化定时器对象
    this->timer1 = new QTimer(this);
    this->timer2 = new QTimer(this);

    //监听正面翻反面的信号
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str= QString(":/new/prefix1/res/Coin000%1.png").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:Opx;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //判断 如果翻完了 将min重置为1
        if(this->min>this->max){
            this->min=1;
            isAnimation = false;//动画结束
            timer1->stop();
        }
    });



    //监听反面翻正面的信号
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str= QString(":/new/prefix1/res/Coin000%1.png").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:Opx;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //判断 如果翻完了 将min重置为1
        if(this->max<this->min){
            this->max=8;
            isAnimation = false;//动画结束
            timer2->stop();
        }
    });
}


//重新按下
void  MyCoin:: mousePressEvent(QMouseEvent* e){
    if(this->isAnimation||this->isWin){
        return;
    }else{
        QPushButton::mousePressEvent(e);
    }
}


//改变标志的方法
void  MyCoin:: changeFlag(){
    //如果是正面 翻成反面
    if(this->flag){
        //开始正面翻反面的定时器
        timer1->start(30);
        isAnimation = true;//动画开始
        this->flag = false;

    }else{//反面翻正面
        timer2->start(30);
        isAnimation = true;//动画开始
        this->flag = true;

    }
}


