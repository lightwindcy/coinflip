#include "coin.h"
#include <QDebug>
#include"playscene.h"
Coin::Coin(QString btnimg){
    QPixmap pix;
    int ret =pix.load(btnimg);
    if(!ret){
        qDebug()<<"金币加载失败";
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    this->time1=new QTimer(this);
    this->time2=new QTimer(this);
    connect(time1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":res/Coin000%1.png").arg(this->min++);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(min>max){
            this->min=1;
            isanimation=false;
            time1->stop();
        }
    });
    connect(time2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":res/Coin000%1.png").arg(this->max--);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(max<min){
            this->max=8;
            isanimation=false;
            time2->stop();
        }
    });
}
void Coin::changeFlag(){
    if(this->flag){
        //开启正面翻反面的定时器
        time1->start(30);
        isanimation=true;
        this->flag=false;
    }else{
        time2->start(30);
        isanimation=true;
        this->flag=true;
    }
}
void Coin::mousePressEvent(QMouseEvent *e){
    if(isanimation||PlayScene::isactive==false){
        return ;
    }
     QPushButton::mousePressEvent(e);
}
