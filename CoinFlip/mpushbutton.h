#ifndef MPUSHBUTTON_H
#define MPUSHBUTTON_H

#include <QPushButton>

class mPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit mPushButton(QWidget *parent = nullptr);
      mPushButton(QString normalImg,QString pressImage="");
      //默认参数
      QString normalImgPath;
      //替换参数
      QString pressImagePath;
void bound1();
void bound2();
void mousePressEvent(QMouseEvent *e);
void mouseReleaseEvent(QMouseEvent *e);


signals:

public slots:
};

#endif // MPUSHBUTTON_H
