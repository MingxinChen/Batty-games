#include "gamefishwin.h"
#include "ui_gamefishwin.h"

GameFishWin::GameFishWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameFishWin)
{
    ui->setupUi(this);
}

GameFishWin::~GameFishWin()
{
    delete ui;
}
