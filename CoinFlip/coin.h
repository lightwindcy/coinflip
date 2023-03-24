#ifndef COIN_H
#define COIN_H
#include <QPushButton>
#include <QWidget>
#include<QTimer>
class Coin : public QPushButton
{
    Q_OBJECT
public:
//    explicit Coin(QWidget *parent = nullptr);
    Coin(QString btnimg);
    //标记每个金币的状态
int x;
int y;
bool flag;
void changeFlag();
//正面翻反面
QTimer * time1;
//反面翻正面
QTimer * time2;
int min =1;
int max= 8;
bool isanimation=false;
void mousePressEvent(QMouseEvent *e);
signals:

public slots:
private:

};

#endif // COIN_H
