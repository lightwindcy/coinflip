#include "playscene.h"
#include<QPainter>
#include <QMenuBar>
#include "mpushbutton.h"
#include<QDebug>
#include<QLabel>
#include"coin.h"
#include"dataconfig.h"
#include<QSound>
#include<QPropertyAnimation>
#include<QTimer>
bool PlayScene::isactive=true;
PlayScene::PlayScene(int val)
{
    //加载音效资源
     QSound * flip_sound= new QSound(":/res/ConFlipSound.wav",this);
      QSound * back_sound= new QSound(":/res/BackButtonSound.wav",this);
       QSound * success_sound= new QSound(":/res/LevelWinSound.wav",this);
    QPixmap pix_s;
    if(!pix_s.load(":/res/LevelCompletedDialogBg.png")){
        qDebug()<<"图片加载失败";
        return;
    }

    this->pass=val;
    setFixedSize(320,588);
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    setWindowTitle("游戏页面");
    QMenuBar *bar = new QMenuBar;
    setMenuBar(bar);
    QMenu *startMenu=bar->addMenu("开始");
    QAction * quitAcion=startMenu->addAction("退出");
    //胜利图标

    QLabel *win_label = new QLabel;
    win_label->setParent(this);
    win_label->setGeometry(0,0,pix_s.width(),pix_s.height());
    win_label->setPixmap(pix_s);
    win_label->move((this->width()-pix_s.width())/2,-pix_s.height());
    mPushButton *back= new mPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    back->setParent(this);
    back->move(this->width()-back->width(),this->height()-back->height());
    connect(back,&QPushButton::clicked,[=](){
        qDebug()<<"返回按钮被点击";
        back_sound->play();
        QTimer::singleShot(500,this,[=](){
            emit playscenesignal();
        });
    });
    //实现显示选择的关卡号
    QLabel *level = new QLabel;
    level->setParent(this);

    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    level->setFont(font);
    QString str= QString("level:%1").arg(val);
    level->setText(str);
    level->setGeometry(QRect(30,this->height()-50,160,50));
    dataConfig *data=new dataConfig;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
        QLabel * grid= new QLabel;

        grid->setParent(this);
        grid->setGeometry(0,0,50,50);
        grid->setPixmap(QPixmap(":/res/BoardNode.png"));
        grid->move(57+i*50,200+j*50);
        //创建金币
        this->datamap[i][j]=data->mData[this->pass][i][j];
        QString coinstr;
        if(datamap[i][j]==1){
            coinstr=":/res/Coin0001.png";
        }else if(datamap[i][j]==0){
            coinstr=":/res/Coin0008.png";
        }
        Coin *coin= new Coin(coinstr);
        coin->setParent(this);
        coin->move(59+i*50,204+j*50);
        coin->x=i;
        coin->y=j;
        coin->flag=datamap[i][j];
        coinBtn[i][j]=coin;
        int dx[4]={1,0,0,-1};
        int dy[4]={0,1,-1,0};
        connect(coin,&Coin::clicked,[=](){
            flip_sound->play();
            coin->changeFlag();
            datamap[i][j]= !datamap[i][j];
            QTimer::singleShot(300,this,[=](){
                for(int count=0;count<4;count++){
                    int newx=dx[count]+coin->x;
                    int newy=dy[count]+coin->y;
                    if(newx<0||newx>=4||newy<0||newy>=4){
                        continue;
                    }
                    coinBtn[newx][newy]->changeFlag();
                }
                int flag=true;
                for(int i=0;i<4;i++){
                    for(int j=0;j<4;j++){
                       if(!coinBtn[i][j]->flag){
                           //游戏失败
//                           qDebug()<<"游戏失败";
                           flag=false;
                           break;
                       }
                    }
                    if(!flag){
                        break;
                    }
                }
                qDebug()<<flag;
                if(flag){
                    success_sound->play();
                    qDebug()<<"游戏胜利";
                   //禁用每个按钮
                    isactive=false;
                    QPropertyAnimation *boundAnime= new QPropertyAnimation(win_label,"geometry");
                    //主要设置其动画效果和其开始位置与结束位置,动画的持续时间
                    boundAnime->setDuration(1000);
                    boundAnime->setStartValue(QRect(win_label->x(),win_label->y(),win_label->width(),win_label->height()));
                     boundAnime->setEndValue(QRect(win_label->x(),win_label->y()+114,win_label->width(),win_label->height()));
                     boundAnime->setEasingCurve(QEasingCurve::OutBounce);
                     boundAnime->start();
                }
            });
        });
        }
    }
}
void PlayScene::paintEvent(QPaintEvent *event){
    QPainter q(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    q.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    q.drawPixmap(10,30,pix);
}
