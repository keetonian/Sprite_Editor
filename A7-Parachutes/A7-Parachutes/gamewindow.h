#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QKeyEvent>

#include "Box2D/Box2D.h"

#include "gamelogic.h"
#include "sprite.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent* e);
    void startGame();
    ~GameWindow();

private:
    Ui::GameWindow *ui;

    GameLogic* game;

    QPixmap pm;

    int scale;

    void connectSignalsAndSlots();

    void setListWidget(QString word);

    QTimer * timer;

    QMediaPlayer* player;


protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

public slots:
    void receiveNewWord(QString word);  // Connected to gameLogic::newWord
    void receiveNewLevel(int level);    // Connected to gameLogic::newLevel
    void receiveFail();                 // Connected to gameLogic::failed
    void receiveVictory();              // Connected to gameLogic::victory
    void actionTimerUpdated(QString message);
    void scoreUpdated(QString score);

signals:
    void letterTyped(QChar letter);
    void newHeight(int);
    void newWidth(int);
    void readyToPlay();

    void pauseGame();
    void unPauseGame();
    void showLevelDial();
private slots:
    void on_actionPause_triggered();
    void on_actionStart_triggered();
    void on_gameOver_triggered();
};

#endif // GAMEWINDOW_H
