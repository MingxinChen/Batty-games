#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "startwin.h"
#include "gamewin.h"
#include "overwin.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void game();
    void over(int score);
    void inital();

private:
    Ui::MainWindow *ui;
    StartWin* startwin;
    GameWin* gamewin;
    OverWin* overwin;
    int overFlag = 0;
};

#endif // MAINWINDOW_H
