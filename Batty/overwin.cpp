#include "overwin.h"
#include "ui_overwin.h"

OverWin::OverWin(QWidget *parent, int score) :
    QWidget(parent),
    ui(new Ui::OverWin)
{
    ui->setupUi(this);
    ui->score->setText("Score: " + QString::number(score));

    this->grabKeyboard();
}

void OverWin::keyPressEvent(QKeyEvent *k)
{
    if(k->key() == Qt::Key_Return || k->key() == Qt::Key_Enter)
        emit returnMenu();
}

OverWin::~OverWin()
{
    delete ui;
}
