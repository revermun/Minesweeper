#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "gamewindow.h"
#include "mywidget.h"

#include <QMainWindow>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void startGame();
    void changeMinesSpinBoxBorders();

private:
    Ui::MainWindow *ui;
    GameWindow game;

};
#endif // MAINWINDOW_H
