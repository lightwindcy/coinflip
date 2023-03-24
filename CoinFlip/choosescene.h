#ifndef CHOOSESCENE_H
#define CHOOSESCENE_H

#include <QMainWindow>
#include "playscene.h"
class ChooseScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
signals:
        void ChooseSignal();
public slots:
private:
        PlayScene *ps;
};


#endif // CHOOSESCENE_H
