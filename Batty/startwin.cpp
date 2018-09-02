#include "startwin.h"
#include "ui_startwin.h"

StartWin::StartWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWin)
{
    ui->setupUi(this);
    this->grabKeyboard();

    ui->startarrow->setVisible(true);
    ui->exitarrow->setVisible(false);
    ui->warning->setVisible(false);
}

void StartWin::keyPressEvent(QKeyEvent *k)
{
    ui->warning->setVisible(false);
    if(k->key() == Qt::Key_Up || k->key() == Qt::Key_Down) {
        if(ui->startarrow->isVisible() == false) {
            ui->startarrow->setVisible(true);
            ui->exitarrow->setVisible(false);
        }
        else {
            ui->startarrow->setVisible(false);
            ui->exitarrow->setVisible(true);
        }
    }
    else if(k->key() == Qt::Key_Left) {
        if(ui->rolearrow->x() <= 20) {
            ui->rolearrow->move(340, ui->rolearrow->y());
        }
        else {
            ui->rolearrow->move(ui->rolearrow->x() - 80, ui->rolearrow->y());
        }
    }
    else if(k->key() == Qt::Key_Right) {
        if(ui->rolearrow->x() >= 340) {
            ui->rolearrow->move(20, ui->rolearrow->y());
        }
        else {
            ui->rolearrow->move(ui->rolearrow->x() + 80, ui->rolearrow->y());
        }
    }
    else if(k->key() == Qt::Key_Enter || k->key() == Qt::Key_Return) {
        if(ui->startarrow->isVisible() == false) {
            qApp->exit(0);
        }
        else {
            if(ui->rolearrow->x() == 20) { //batty
                emit startGame();
            }
            else if(ui->rolearrow->x() == 340) { //fish
                emit startGame_fish();
            }
            else {
                ui->warning->setVisible(true);
            }
        }
    }
}

void StartWin::keyReleaseEvent(QKeyEvent *k)
{

}

StartWin::~StartWin()
{
    delete ui;
}
