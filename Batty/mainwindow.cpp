#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    startwin = new StartWin(this);
    startwin->show();
    startwin->move(200, 150);

    QObject::connect(startwin, SIGNAL(startGame()), this, SLOT(game()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::inital()
{
    qApp->closeAllWindows();
    QProcess::startDetached(qApp->applicationFilePath(), QStringList());
}

void MainWindow::game()
{
    startwin->close();

    gamewin = new GameWin(this);
    QObject::connect(gamewin, SIGNAL(gameover(int)), this, SLOT(over(int)));
    gamewin->show();
}

void MainWindow::over(int score)
{
    gamewin->close();

    overwin = new OverWin(this, score);
    QObject::connect(overwin, SIGNAL(returnMenu()), this, SLOT(inital()));
    overwin->show();
    overwin->move(200, 150);
}
