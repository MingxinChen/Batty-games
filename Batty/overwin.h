#ifndef OVERWIN_H
#define OVERWIN_H

#include <QWidget>
#include <QKeyEvent>

namespace Ui {
class OverWin;
}

class OverWin : public QWidget
{
    Q_OBJECT

public:
    explicit OverWin(QWidget *parent = 0, int score = 0);
    ~OverWin();

protected:
    virtual void keyPressEvent(QKeyEvent *k);

signals:
    void returnMenu();

private:
    Ui::OverWin *ui;
};

#endif // OVERWIN_H
