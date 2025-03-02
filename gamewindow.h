#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QPainter>
#include <QWidget>
#include <QMainWindow>
#include "minefield.h"
#include "QTimer"
#include "QString"
#include "commonfiles.h"


QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void showEvent(QShowEvent *event) override;

    unsigned minesCount;
    unsigned rows;
    unsigned columns;

protected:
    void paintEvent(QPaintEvent* event) override;

public slots:
    void returnToMenu();
    void regenerateField();
    void timerTick();
    void timerSet();
    void timerStop();
    void changeCounter();
private:
    void draw(QPainter& p);
    QTimer *timer;
    int minesRemain;
    unsigned time;
    Ui::GameWindow *ui;
};


#endif // GAMEWINDOW_H
