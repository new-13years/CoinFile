#include "playscene.h"

#include "MyPushButton.h"
#include "dataconfig.h"

#include <QLabel>
#include <QMenuBar>
#include <QPainter>
#include <QPropertyAnimation>
#include <QSoundEffect>
#include <QTimer>
#include "MyCoin.h"
// PlayScene::PlayScene(QWidget *parent)
//     : QMainWindow{parent}
// {}

PlayScene::PlayScene(int levelNum){
    QString str = QString("进入了第 %1 关").arg(levelNum);
    qDebug()<<str;
    this->levelNum = levelNum;
    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QIcon(":/new/prefix1/res/Coin0001.png"));
    //设置标题
    QString strlevel = QString("第 %1 关").arg(levelNum);
    this->setWindowTitle(strlevel);

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

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/new/prefix1/res/BackButton.png",":/new/prefix1/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //返回按钮的音效
    QSoundEffect *backSound = new QSoundEffect(this);
    backSound->setSource(QUrl::fromLocalFile(":/new/prefix1/res/BackButtonSound.wav"));

    //翻金币音效
    QSoundEffect *coinSound = new QSoundEffect(this);
    coinSound->setSource(QUrl::fromLocalFile(":/new/prefix1/res/ConFlipSound.wav"));

    //胜利音效
    QSoundEffect *winSound = new QSoundEffect(this);
    winSound->setSource(QUrl::fromLocalFile(":/new/prefix1/res/LevelWinSound.wav"));
    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        backSound->play();
        qDebug()<<"游戏关卡内点击了返回按钮";
        //告诉 关卡选择 场景 ：我返回了 ，关卡选择 监听ChooseLevelScene 的返回按钮
        //延时返回 发送自定义信号
        QTimer::singleShot(200,this,[=](){
            emit this->gameBack();
        });

    });
    //显示当前关卡数
    QLabel *label = new QLabel;
    label->setParent(this);

    //设置个性化字体
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString strlevel1 = QString("Level: %1").arg(this->levelNum);
    //将字体设置到 Label 中
    label->setFont(font);
    label->setText(strlevel1);

    label->setGeometry(30,this->height()-50,120,50);

    dataConfig config;
    //初始化每个关卡的二维数组
    for(int i= 0;i<4;i++){
        for(int j= 0;j<4;j++){
            this->gameArray[i][j] = config.mData[this->levelNum][i][j];
        }

    }

    //胜利图片（先放窗口外面）
    QLabel * winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/new/prefix1/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());



    //显示金币的背景图案
    for(int i = 0 ;i<4;i++){
        for(int j=0;j<4;j++){
         //绘制背景图片
            QPixmap pix = QPixmap(":/new/prefix1/res/BoardNode(1).png");
            QLabel *label = new QLabel;
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57+i*50,200+j*50);

            //创建金币或银币
            QString  strPath;

            if(this->gameArray[i][j]==1){
                 strPath = ":/new/prefix1/res/Coin0001.png";
            }
            else{
                 strPath = ":/new/prefix1/res/Coin0008.png";
            }
            MyCoin *coin = new MyCoin(strPath);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);

            //给金币的属性赋值
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j]; //1正面  0反面

            //将金币放入到 金币的二维数组里
            coinBtn[i][j] = coin;
            //点击金币 进行翻转



            connect(coin,&MyCoin::clicked,[=](){
                coinSound->play();//播放翻金币音效
            //点击之后先禁用所有按钮 等翻完之后在解开所有按钮
            for(int i = 0;i<4;i++){
                for(int j = 0;j<4;j++){
                    this->coinBtn[i][j]->isWin=true;
                }
            }
            coin->changeFlag();
            this->gameArray[i][j] = this->gameArray[i][j]==0 ? 1: 0;

                //翻转周围金币 ,延时翻转
                QTimer::singleShot(20,this,[=](){


                    if(coin->posX+1<=3){//金币右侧金币的翻转
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[i][j] = this->gameArray[i][j]==0 ? 1: 0;
                    }
                    if(coin->posX-1>=0){//金币左侧金币的翻转
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[i][j] = this->gameArray[i][j]==0 ? 1: 0;
                    }
                    if(coin->posY-1>=0){//金币上侧金币的翻转
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[i][j] = this->gameArray[i][j]==0 ? 1: 0;
                    }
                    if(coin->posY+1<=3){//金币下侧金币的翻转
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[i][j] = this->gameArray[i][j]==0 ? 1: 0;
                    }

                    //等翻完之后在解开所有按钮
                    for(int i = 0;i<4;i++){
                        for(int j = 0;j<4;j++){
                            this->coinBtn[i][j]->isWin=false;
                        }
                    }

                    //判断是否胜利
                    this->isWin = true;
                    for(int i=0;i<4;i++){
                        for(int j=0;j<4;j++){
                            if(coinBtn[i][j]->flag==false){//只要有一个是反面，那就算失败
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if(this->isWin==true){  //胜利了
                        winSound->play();//播放胜利音效
                        qDebug()<<"游戏胜利";
                        for(int i = 0;i<4;i++){
                            for(int j = 0;j<4;j++){
                                this->coinBtn[i][j]->isWin=true;
                            }
                        }

                        //将胜利图片移动下来
                        QPropertyAnimation * animation = new QPropertyAnimation(winLabel,"geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //设置开始位置
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        //设置结束位置
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //执行动画
                        animation->start();

                    }
                });

            });
        }
    }
}


//重写绘图事件
void PlayScene::paintEvent(QPaintEvent * e){

    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/new/prefix1/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画背景上图标
    pix.load(":/new/prefix1/res/Title.png");

    pix = pix.scaled(pix.width()*0.6,pix.height()*0.6);

    painter.drawPixmap(10,30,pix);

}

