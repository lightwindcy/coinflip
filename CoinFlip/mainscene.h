#ifndef MAINSCENE_H
#define MAINSCENE_H
#include<QPainter>
#include <QMainWindow>
#include "ChooseScene.h"
namespace Ui {
class MainScene;
}

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = 0);
    ~MainScene();
    void paintEvent(QPaintEvent *);

private:
    Ui::MainScene *ui;
    ChooseScene *chooseScene;
};

#endif // MAINSCENE_H
