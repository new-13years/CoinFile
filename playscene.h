#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "MyCoin.h"

#include <QMainWindow>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int leveNum);
    int levelNum; //内部成员属性 ，记录所选关卡

    //重写绘图事件
    void paintEvent(QPaintEvent *)override;

    int gameArray[4][4];//二维数组 维护每关卡的具体数据

    MyCoin * coinBtn[4][4];//维护金币数组

    bool isWin; //是否胜利

signals:
    void gameBack();
};

#endif // PLAYSCENE_H
