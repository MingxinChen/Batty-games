#ifndef GAMEFISHWIN_H
#define GAMEFISHWIN_H

#include <QWidget>

namespace Ui {
class GameFishWin;
}

class GameFishWin : public QWidget
{
    Q_OBJECT

public:
    explicit GameFishWin(QWidget *parent = 0);
    ~GameFishWin();

private:
    Ui::GameFishWin *ui;
};

#endif // GAMEFISHWIN_H
