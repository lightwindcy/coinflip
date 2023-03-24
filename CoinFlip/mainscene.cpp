#include "mainscene.h"
#include "ui_mainscene.h"
#include "mpushbutton.h"
#include <qtimer.h>
#include<QSound>
MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);
    setFixedSize(320,588);
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    setWindowTitle("翻金币主页");
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });
    mPushButton * MainScene_Button= new mPushButton(":/res/MenuSceneStartButton.png");
    MainScene_Button->setParent(this);
    MainScene_Button->move(this->width()*0.5-MainScene_Button->width()*0.5,this->height()*0.7);
    //绑定按钮按下信号的槽函数
     QSound * startsound= new QSound(":/res/TapButtonSound.wav",this);
   ChooseScene * chooseScene=new ChooseScene;
    connect(MainScene_Button,&mPushButton::clicked,[=](){

        startsound->play();
        MainScene_Button->bound1();
        MainScene_Button->bound2();

        //时间触发事件
        QTimer::singleShot(500,this,[=](){
            this->hide();
            chooseScene->setGeometry(this->geometry());
            chooseScene->show();
        });
    });
    connect(chooseScene,&ChooseScene::ChooseSignal,[=]{
        this->setGeometry(chooseScene->geometry());
        chooseScene->hide();
        this->show();
    });

}
void MainScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}

MainScene::~MainScene()
{
    delete ui;
}
