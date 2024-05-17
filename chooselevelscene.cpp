#include "chooselevelscene.h"

#include <MyPushButton.h>
#include <QLabel>
#include <QMenuBar>
#include<QPainter>
#include <QSoundEffect>
#include <QTimer>

ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    //配置 选择关卡 场景
    this->setFixedSize(320,588);

    //设置图标
    this->setWindowIcon(QPixmap(":/new/prefix1/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("选择关卡");

    //创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);
    //创建开始菜单
    QMenu *startMenu = bar->addMenu("开始");
    //创建退出 菜单项
    QAction * quitAction = startMenu->addAction("退出");
    //点击退出 实现退出游戏

    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //选择关卡按钮的音效
    QSoundEffect *chooseSound = new QSoundEffect(this);
    chooseSound->setSource(QUrl::fromLocalFile(":/new/prefix1/res/TapButtonSound.wav"));


    MyPushButton * backBtn = new MyPushButton(":/new/prefix1/res/BackButton.png",":/new/prefix1/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //返回按钮的音效
    QSoundEffect *backSound = new QSoundEffect(this);
    backSound->setSource(QUrl::fromLocalFile(":/new/prefix1/res/BackButtonSound.wav"));


    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        backSound->play();//播放音效
        //qDebug()<<"点击了返回按钮";
        //告诉主场景 ：我返回了 ，主场景监听ChooseLevelScene 的返回按钮
        //延时返回 发送自定义信号
        QTimer::singleShot(200,this,[=](){
            emit this->chooseSceneBack();
        });

    });

    //创建选择关卡的按钮
    for(int i = 0;i<20;i++){
        MyPushButton * menuBtn = new MyPushButton(":/new/prefix1/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+i%4*70,130+i/4*70);

        //监听每个按钮的点击事件
        connect(menuBtn,&MyPushButton::clicked,[=](){
            chooseSound->play();//播放音效
            this->hide();//将选关场景隐藏掉
            //进入到游戏场景
            play = new PlayScene(i+1);

            play->setGeometry(this->geometry());//设置play场景窗口框与自身一致

            play->show();
            //监听游戏类的返回信号
            connect(play,&PlayScene::gameBack,this,[=](){
                this->setGeometry(play->geometry());//设置自身窗口框与play场景一致
                this->show();
                delete play;
                play = nullptr;
            });
        });

        //添加Label框 覆盖按钮键 放置关卡文字
        QLabel *label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(25+i%4*70,130+i/4*70);

        //设置 laebl 上的对齐方式
        label->setAlignment(Qt::AlignHCenter| Qt::AlignVCenter);
        //设置让鼠标进行穿透属性 51
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}
//重写绘图事件
void ChooseLevelScene::paintEvent(QPaintEvent *){
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/new/prefix1/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画背景上图标
    pix.load(":/new/prefix1/res/Title.png");

    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
