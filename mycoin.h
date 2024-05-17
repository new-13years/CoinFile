#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    //参数代表 传入的金币路径 还是银币路径
    MyCoin(QString btnImg);

    //金币的属性
    int posX;//X坐标位置
    int posY;//Y坐标位置
    bool flag;//正反标识

    //改变标志的方法
    void  changeFlag();

    QTimer *timer1;//正面翻反面的定时器
    QTimer *timer2;//反面翻正面的定时器
    int min = 1;
    int max = 8;

    //执行动画的标志
    bool isAnimation = false;//翻转动画进行中的标志

    //重新按下
    void mousePressEvent(QMouseEvent*)override;

    bool isWin ;//是否胜利
signals:
};

#endif // MYCOIN_H
