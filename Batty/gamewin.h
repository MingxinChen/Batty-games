#ifndef GAMEWIN_H
#define GAMEWIN_H

#include <QWidget>
#include <QKeyEvent>
#include <QSet>
#include <QLabel>
#include <QTime>
#include <QMovie>
#include <QThread>

static int battyHeight = 70;
static int battyWidth = 60;
static int batHeight = 20;
static int batWidth = 50;
static int monsterHeight = 70;
static int monsterWidth = 60;
static int moveStep = 20;
static int gamewinHeight = 500;
static int gamewinWidth = 800;

namespace Ui {
class GameWin;
}

class GameWin : public QWidget
{
    Q_OBJECT

public:
    explicit GameWin(QWidget *parent = 0);
    ~GameWin();

protected:
    virtual void keyPressEvent(QKeyEvent *k);
    virtual void keyReleaseEvent(QKeyEvent *k);
    virtual void timerEvent(QTimerEvent *e);

signals:
    void gameover(int score);

private:
    Ui::GameWin *ui;
    int posX, posY;
    int score;
    int life;
    int batSpeed, monsterSpeed, monsterAppear;
    int monsterMaxNum;

    QSet<QLabel*> batSet;
    QSet<QLabel*> monsterSet;

    void moveBatty(int posX, int posY);
    void setScore(int score);
    void setLife(int life);
    void shotting(int lowX, int lowY);
    void getScore();
};

#endif // GAMEWIN_H
