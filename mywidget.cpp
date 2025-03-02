#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{

}

void MyWidget::generateField()
{

    std::vector<std::vector<bool>> mineMatrix;
    for(int i = 0; i<this->columns; i++){
        std::vector<bool> mineVector;
        for (int j = 0; j<this->rows; j++){

            mineVector.push_back(0);
        }
        mineMatrix.push_back(mineVector);
    }
    int minesPlanted = 0;
    while (minesPlanted!=minesCount){
        int x = rand()%columns;
        int y = rand()%rows;
        if (mineMatrix[x][y]==0){
            mineMatrix[x][y] = 1;
            minesPlanted++;
        }
    }

    field = MineField(mineMatrix);
    field.setMinesCount(this->minesCount);
    emit clicked();
    field.setRows(this->rows);
    field.setColumns(this->columns);
    update();
}

void MyWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    field.draw(painter);
//    painter.end();
}


void MyWidget::mouseMoveEvent(QMouseEvent *event)
{

}


void MyWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        unsigned x = event->position().x()/32;
        unsigned y = event->position().y()/32;
        if ((x < field.layout.size()) && (y < field.layout[0].size())){
            field.reveal(x,y);
            update();
            if (field.getGamestate()!= Ongoing){ emit gameEnded();}
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        unsigned x = event->position().x()/32;
        unsigned y = event->position().y()/32;
        if ((x < field.layout.size()) && (y < field.layout[0].size())){
            field.flag(x,y);
            update();
            if (field.getGamestate()!= Ongoing){ emit gameEnded();}
        }
    }
    emit clicked();
}

void MyWidget::mouseReleaseEvent(QMouseEvent *event){
    mouseHold = false;
}
