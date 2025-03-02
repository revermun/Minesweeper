#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QPainter>
#include <QWidget>
#include <QMouseEvent>
#include <iostream>
#include <QMenu>

#include "minefield.h"
#include "gamewindow.h"

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);
    void generateField();

    unsigned minesCount;
    unsigned rows;
    unsigned columns;
    MineField field;
signals:
    void gameEnded();
    void clicked();

protected:
    void paintEvent(QPaintEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;


private:
    QBrush brush = QBrush(Qt::gray,Qt::SolidPattern);
    bool mouseHold;


};
#endif // MYWIDGET_H
