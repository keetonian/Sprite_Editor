#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <sprite.h>
#include <QPainter>
#include <QTimer>
#include "gameLogic.h"
#include "Box2D/Box2D.h"
#include <QDebug>
#include <QKeyEvent>


namespace Ui {
class gameWindow;
}

class gameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit gameWindow(QWidget *parent = 0);
    ~gameWindow();

private:
    Ui::gameWindow *ui;

    Sprite sprite;

    gameLogic* game;

    int scale;

    void connectSignalsAndSlots();

    void setListWidget(QString word);

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent * event);

public slots:
    void receiveNewWord(QString word); //Connected to gameLogic::newWord
    void receiveNewLevel(int level);//Connected to gameLogic::newLevel
    void receiveFail();//Connected to gameLogic::failed
    void receiveVictory();//Connected to gameLogic::victory

signals:
    void letterTyped(char letter);
};

#endif // GAMEWINDOW_H
