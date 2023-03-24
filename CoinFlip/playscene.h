#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "coin.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
//    explicit PlayScene(QWidget *parent = nullptr);
    //pass为关卡值
    PlayScene(int p);
    void paintEvent(QPaintEvent *event);
    int pass;
    int datamap[4][4];
    Coin * coinBtn[4][4];
    static bool isactive;

signals:    void playscenesignal();
public slots:
private:

};
#endif // PLAYSCENE_H
