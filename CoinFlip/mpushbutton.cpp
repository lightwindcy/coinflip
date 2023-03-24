#include "mpushbutton.h"
#include<QDebug>
#include<QPropertyAnimation>
mPushButton::mPushButton(QString normalImg,QString pressImage){
     this->normalImgPath =normalImg;
    this->pressImagePath= pressImage;
    QPixmap pix;
    if(!pix.load(normalImg)){
        qDebug()<<"图片加载失败";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

 }
void mPushButton::bound1(){
    QPropertyAnimation *boundAnime= new QPropertyAnimation(this,"geometry");
    //主要设置其动画效果和其开始位置与结束位置,动画的持续时间
    boundAnime->setDuration(200);
    boundAnime->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
     boundAnime->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
     boundAnime->setEasingCurve(QEasingCurve::OutBounce);
     boundAnime->start();
}

void mPushButton::bound2(){
    QPropertyAnimation *boundAnime= new QPropertyAnimation(this,"geometry");
    //主要设置其动画效果和其开始位置与结束位置,动画的持续时间
    boundAnime->setDuration(200);
    boundAnime->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
     boundAnime->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
     boundAnime->setEasingCurve(QEasingCurve::OutBounce);
     boundAnime->start();
}
void mPushButton::mousePressEvent(QMouseEvent *e){
    if(this->pressImagePath!=""){
        QPixmap q;
        bool ret = q.load(this->pressImagePath);
        if(!ret){
            qDebug()<<"退出按钮加载失败";
            return;
        }
        this->setFixedSize(this->width(),this->height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(QIcon(q));
        this->setIconSize(QSize(this->width(),this->height()));
    }
     return QPushButton::mousePressEvent(e);
}

void mPushButton::mouseReleaseEvent(QMouseEvent *e){
    if(this->pressImagePath!=""){
        QPixmap q;
        bool ret = q.load(this->normalImgPath);
        if(!ret){
            qDebug()<<"退出按钮加载失败";
            return;
        }
        this->setFixedSize(this->width(),this->height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(QIcon(q));
       this->setIconSize(QSize(this->width(),this->height()));
    }
     return QPushButton::mouseReleaseEvent(e);
}

