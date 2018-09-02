#include "gamewin.h"
#include "ui_gamewin.h"

bool coincide(int battyX, int battyY, int monX, int monY);

GameWin::GameWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWin)
{
    ui->setupUi(this);

    this->moveBatty(gamewinWidth / 2 - battyWidth / 2, gamewinHeight - battyHeight);
    this->setScore(0);
    this->setLife(3);
    this->batSpeed = startTimer(10);
    this->monsterSpeed = startTimer(15);
    this->monsterAppear = startTimer(2000);
    this->monsterMaxNum = 5;

    QMovie* img = new QMovie(":/new/images/img/蝙蝠侠.gif");
    ui->batty->setMovie(img);
    img->start();


    this->grabKeyboard();
}

GameWin::~GameWin()
{
    delete ui;
}

void GameWin::keyPressEvent(QKeyEvent *k)
{
    if(k->key() == Qt::Key_W || k->key() == Qt::Key_Up) {
        this->moveBatty(posX, posY - moveStep);
    }
    else if(k->key() == Qt::Key_S || k->key() == Qt::Key_Down) {
        this->moveBatty(posX, posY + moveStep);
    }
    else if(k->key() == Qt::Key_A || k->key() == Qt::Key_Left) {
        this->moveBatty(posX - moveStep, posY);
    }
    else if(k->key() == Qt::Key_D || k->key() == Qt::Key_Right) {
        this->moveBatty(posX + moveStep, posY);
    }
    else if(k->key() == Qt::Key_Space) {
        this->shotting(posX, posY);
    }
}

void GameWin::keyReleaseEvent(QKeyEvent *k)
{

}

void GameWin::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == batSpeed) {
        foreach (QLabel* b, batSet) {
            b->move(b->x(), b->y() - 1);

            foreach(QLabel* m, monsterSet) {
                if(b->y() < m->y() + monsterHeight && b->y() > m->y() &&
                        b->x() + batWidth > m->x() && b->x() + batWidth < m->x() + monsterWidth) {
                    this->getScore();

                    b->setVisible(false);
                    b->deleteLater();
                    batSet.erase(batSet.find(b));

                    QPixmap img;
                    img.load(":/new/images/img/爆炸.png");
                    m->setPixmap(img);
                    //m->setVisible(false);
                    //m->deleteLater();
                    monsterSet.erase(monsterSet.find(m));
                    break;
                }
            }

            if(b->y() + batHeight <= 0) {
                b->deleteLater();
                batSet.erase(batSet.find(b));
            }
        }
    }
    else if(e->timerId() == monsterSpeed) {
        foreach (QLabel* m, monsterSet) {
            m->move(m->x(), m->y() + 1);

            if(coincide(this->posX, this->posY, m->x(), m->y())) {
                QMovie* img = new QMovie(":/new/images/img/爆炸.gif");
                ui->batty->setMovie(img);
                img->start();
                QThread::msleep(1000);

                img = new QMovie(":/new/images/img/蝙蝠侠.gif");
                ui->batty->setMovie(img);
                img->start();

                this->setLife(this->life - 1);

                m->deleteLater();
                monsterSet.erase(monsterSet.find(m));
            }

            if(m->y() - monsterHeight >= gamewinHeight) {
                m->deleteLater();
                monsterSet.erase(monsterSet.find(m));
            }
        }
    }
    else if(e->timerId() == monsterAppear) {
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        int monsterNum = qrand() % monsterMaxNum;
        while(monsterNum--) {
            QMovie* img = new QMovie(":/new/images/img/小怪兽.gif");

            QLabel* m = new QLabel(this);
            m->setMovie(img);
            img->start();
            m->setScaledContents(true);
            m->resize(monsterWidth, monsterHeight);
            m->move(qrand() % (gamewinWidth- monsterWidth), -1 * monsterHeight);
            m->setVisible(true);

            this->monsterSet.insert(m);
        }
    }
}

void GameWin::moveBatty(int posX, int posY)
{
    if(posX >= 0 && posY >= 0 &&
            posX + battyWidth <= gamewinWidth && posY + battyHeight <= gamewinHeight) {
        this->posX = posX;
        this->posY = posY;
        ui->batty->move(posX, posY);
    }
}

void GameWin::setScore(int score)
{
    this->score = score;
    ui->score->setText("Score: " + QString::number(score));
}

void GameWin::setLife(int life)
{
    this->life = life;
    ui->life1->setVisible(false);
    ui->life2->setVisible(false);
    ui->life3->setVisible(false);

    if(life == 0) {
        emit gameover(score);
    }
    if(life >= 1) {
        ui->life1->setVisible(true);
    }
    if(life >= 2) {
        ui->life2->setVisible(true);
    }
    if(life >= 3) {
        ui->life3->setVisible(true);
    }
}

void GameWin::shotting(int lowX, int lowY)
{
    QPixmap img;
    img.load(":/new/images/img/bat.png");

    QLabel* bat = new QLabel(this);
    bat->setPixmap(img);
    bat->setScaledContents(true);
    bat->resize(batWidth, batHeight);
    bat->move(lowX + (battyWidth - batWidth) / 2, lowY - batHeight);
    bat->setVisible(true);

    this->batSet.insert(bat);
}

void GameWin::getScore()
{
    setScore(this->score + 1);


}

bool coincide(int battyX, int battyY, int monX, int monY)
{
    if(battyX >= monX && battyX <= monX + monsterWidth && battyY >= monY && battyY <= monY + monsterHeight) {
        return true;
    }
    battyX += battyWidth;
    if(battyX >= monX && battyX <= monX + monsterWidth && battyY >= monY && battyY <= monY + monsterHeight) {
        return true;
    }
    battyY += battyHeight;
    if(battyX >= monX && battyX <= monX + monsterWidth && battyY >= monY && battyY <= monY + monsterHeight) {
        return true;
    }
    battyX -= battyWidth;
    if(battyX >= monX && battyX <= monX + monsterWidth && battyY >= monY && battyY <= monY + monsterHeight) {
        return true;
    }

    battyY -= battyHeight;
    if(monX >= battyX && monX <= battyX + battyWidth && monY >= battyY && monY <= battyY + battyHeight) {
        return true;
    }
    monX += monsterWidth;
    if(monX >= battyX && monX <= battyX + battyWidth && monY >= battyY && monY <= battyY + battyHeight) {
        return true;
    }
    monY += monsterHeight;
    if(monX >= battyX && monX <= battyX + battyWidth && monY >= battyY && monY <= battyY + battyHeight) {
        return true;
    }
    monX -= monsterWidth;
    if(monX >= battyX && monX <= battyX + battyWidth && monY >= battyY && monY <= battyY + battyHeight) {
        return true;
    }

    return false;
}
