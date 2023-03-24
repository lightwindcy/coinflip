#include "choosescene.h"
#include <QMenuBar>
#include<QPainter>
#include"mpushbutton.h"
#include<QDebug>
#include<QLabel>
#include "playscene.h"
#include<QSound>
#include<QTimer>
ChooseScene::ChooseScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(320,588);
    this->setWindowIcon(QIcon(":res/Coin0001.png"));
    this->setWindowTitle("选择关卡");
    //创建菜单
    QMenuBar *bar = new QMenuBar;
    setMenuBar(bar);
    QMenu *startMenu=bar->addMenu("开始");
    QAction * quitAcion=startMenu->addAction("退出");
    connect(quitAcion,&QAction::triggered,[=](){
        this->close();
    });
    mPushButton *back= new mPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    back->setParent(this);
    back->move(this->width()-back->width(),this->height()-back->height());
     QSound* back_music= new QSound(":/res/BackButtonSound.wav",this);
    connect(back,&mPushButton::clicked,[=](){
        qDebug()<<"返回按钮被点击";
        back_music->play();
        QTimer::singleShot(500,this,[=](){
            emit ChooseSignal();
        });
    });
    //创建关卡
    QSound* choose_music= new QSound(":/res/TapButtonSound.wav",this);
    for(int i=0;i<20;i++){
        mPushButton *qPass = new mPushButton(":/res/LevelIcon.png");
        qPass->setParent(this);
        qPass->move(25+i%4*70,130+i/4*70);
        connect(qPass,&mPushButton::clicked,[=](){
            choose_music->play();
            QString str = QString("你选择的是%1关").arg(i+1);
            qDebug()<<str;
            this->hide();
            this->ps= new PlayScene(i+1);
            ps->setGeometry(this->geometry());
            this->ps->show();
            connect(ps,&PlayScene::playscenesignal,[=]{
                this->setGeometry(ps->geometry());
                this->show();
               delete ps;
                ps=nullptr;
            });
        });
        QLabel *label = new QLabel(QString::number(i+1),this);
        label->setFixedSize(qPass->width(),qPass->height());
        label->move(25+i%4*70,130+i/4*70);
        label->setAlignment(Qt::AlignCenter);
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}
void ChooseScene::paintEvent(QPaintEvent *event){
    QPainter q(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    q.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    q.drawPixmap(10,30,pix);

}
