#ifndef STARTWIN_H
#define STARTWIN_H

#include <QWidget>
#include <QMainWindow>
#include <QKeyEvent>

namespace Ui {
class StartWin;
}

class StartWin : public QWidget
{
    Q_OBJECT

public:
    explicit StartWin(QWidget *parent = 0);
    ~StartWin();

protected:
    virtual void keyPressEvent(QKeyEvent *k);
    virtual void keyReleaseEvent(QKeyEvent *k);

signals:
    void startGame();
    void startGame_fish();

private:
    Ui::StartWin *ui;
};

#endif // STARTWIN_H
