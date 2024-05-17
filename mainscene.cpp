#include "mainscene.h"
#include "ui_mainscene.h"

#include <MyPushButton.h>
#include <QPainter>
#include <QTimer>
#include <QSoundEffect> //多媒体模块下面的音效头文件


MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //配置主场景

    //设置固定大小
    setFixedSize(320,588);

    //设置图标
    setWindowIcon(QIcon(":/new/prefix1/res/Coin0001.png"));

    //设置标题
    setWindowTitle("翻金币主场景");

    //退出按钮实现
    connect(ui->actionQuit,&QAction::triggered,[=](){
        this->close();
    });

    //准备开始按钮的音效
    QSoundEffect *startSound = new QSoundEffect(this);
    startSound->setSource(QUrl::fromLocalFile(":/new/prefix1/res/TapButtonSound.wav"));
    // startSound->setVolume(0.25f);

    //开始按钮
    MyPushButton *startBtn = new MyPushButton(":/new/prefix1/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move((this->width()-startBtn->width())*0.5,this->height()*0.7);

    //实例化选择关卡场景
    chooseScene = new ChooseLevelScene;

    //监听选择关卡的返回按钮的信号
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,this,[=](){
        this->setGeometry(chooseScene->geometry());//设置主场景与 选择关卡场景 一致

        chooseScene->hide();//将选择关卡场景隐藏掉
        this->show();//重新显示主场景
    });


    connect(startBtn,&QPushButton::clicked,[=](){
        qDebug()<<"点击了开始按钮";
        startSound->play();//播放开始按钮音效
        //调用弹起特效
        startBtn->zoom1();
        //startBtn->zoom2();

        //延时进入到 选择关卡 场景中
        QTimer::singleShot(200,this,[=](){

            //设置chooseScene场景的位置与 主场景 一致
            chooseScene->setGeometry(this->geometry());


            //自身隐藏
            this->hide();
            //显示 选择关卡 场景
            chooseScene->show();
        });
    });
}

//重写paintevent事件 画背景图
void MainScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/new/prefix1/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画背景上图标
    pix.load(":/new/prefix1/res/Title.png");

    pix = pix.scaled(pix.width()*0.6,pix.height()*0.6);

    painter.drawPixmap(10,30,pix);
}

MainScene::~MainScene()
{
    delete ui;
}
