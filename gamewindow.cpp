#include "gamewindow.h"
#include "ui_gamewindow.h"


GameWindow::GameWindow(QWidget *parent): QWidget(parent), ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    minesRemain = minesCount;
    changeCounter();
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::showEvent(QShowEvent *event)
{
    timerSet();
    ui->minefieldWidget->rows = this->rows;
    ui->minefieldWidget->columns = this->columns;
    ui->minefieldWidget->minesCount = this->minesCount;
    this->setGeometry(100,200,20+32*columns,60+32*rows);
    this->setFixedSize(20+32*columns,60+32*rows);
    ui->minefieldWidget->setGeometry(10,50,32*columns,32*rows);
    ui->minefieldWidget->generateField();
    ui->regenerateButton->setGeometry(10,10,31,31);
    ui->regenerateButton->setIcon(QIcon("commonicons/restart.png"));

}

void GameWindow::returnToMenu()
{

}

void GameWindow::timerSet()
{
    time = 0;
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTick()));
    timer->start(10);
}
void GameWindow::timerTick()
{
    time++;
    update();
}
void GameWindow::regenerateField()
{
    time = 0;
    timer->start(10);
    ui->minefieldWidget->generateField();
    changeCounter();
}

void GameWindow::timerStop()
{
    timer->stop();
}

void GameWindow::changeCounter()
{
    minesRemain = int(ui->minefieldWidget->field.getMinesCount()) - int(ui->minefieldWidget->field.getFlagedCellsCount());
}

void GameWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    draw(painter);
//    painter.end();
}

QString getFilenameFromNumber(int number)
{
    QString fileName = "";
    switch (number)
    {
        case 0: {fileName = REDZEROFILE; break;}
        case 1: {fileName = REDONEFILE; break;}
        case 2: {fileName = REDTWOFILE;  break;}
        case 3: {fileName = REDTHREEFILE; break;}
        case 4: {fileName = REDFOURFILE; break;}
        case 5: {fileName = REDFIVEFILE; break;}
        case 6: {fileName = REDSIXFILE;  break;}
        case 7: {fileName = REDSEVENFILE; break;}
        case 8: {fileName = REDEIGHTFILE; break;}
        case 9: {fileName = REDNINEFILE; break;}
        default:{fileName = REDZEROFILE; break;}
    }
    return fileName;
}

void GameWindow::draw(QPainter& p)
{

    QRectF source(0.0, 0.0, 32.0, 32.0);
    QString fileName = "";
    unsigned second1 = time/100%10;
    unsigned second10 = time/1000%10;
    unsigned second100 = time/10000%10;
    unsigned mines1 = minesRemain%10;
    unsigned mines10 = minesRemain/10%10;
    if (columns==5 and rows == 5)
    {
        unsigned xstart = 10 + 32 + 16;
        fileName = getFilenameFromNumber(second10);
        p.drawPixmap(QRectF(xstart, 10, 32.0, 32.0), QPixmap(fileName), source);
        fileName = getFilenameFromNumber(second1);
        p.drawPixmap(QRectF(xstart + 32, 10, 32.0, 32.0), QPixmap(fileName), source);
        fileName = getFilenameFromNumber(mines1);
        p.drawPixmap(QRectF(10+ 32*4, 10, 32.0, 32.0), QPixmap(fileName), source);
    }
    else if (columns == 5 and rows == 6)
    {
        unsigned xstart = 20 + (32*columns);
        unsigned ystart = 10;
        this->setFixedSize(30+32*(columns+1),20+32*rows);
        ui->minefieldWidget->setGeometry(10,10,32*columns,32*rows);
        ui->regenerateButton->setGeometry(xstart,ystart,31,31);
        fileName = getFilenameFromNumber(second100);
        p.drawPixmap(QRectF(xstart, ystart, 32.0, 32.0), QPixmap(fileName), source);
        fileName = getFilenameFromNumber(second10);
        p.drawPixmap(QRectF(xstart, ystart + 32*2, 32.0 , 32.0), QPixmap(fileName), source);
        fileName = getFilenameFromNumber(second1);
        p.drawPixmap(QRectF(xstart, ystart + 32*3, 32.0 , 32.0), QPixmap(fileName), source);
        fileName = getFilenameFromNumber(mines1);
        p.drawPixmap(QRectF(xstart, ystart + 32*5, 32.0, 32.0), QPixmap(fileName), source);
    }
    else if (columns == 6 or columns == 7)
    {
        unsigned xstart = 25 + (32*(columns-2))/2;
        unsigned xend = 10 + 32*(columns-1);
        fileName = getFilenameFromNumber(second10);
        p.drawPixmap(QRectF(xstart - 32.0, 10, 32.0, 32.0), QPixmap(fileName), source);
        fileName = getFilenameFromNumber(second1);
        p.drawPixmap(QRectF(xstart, 10, 32.0, 32.0), QPixmap(fileName), source);
        fileName = getFilenameFromNumber(mines1);
        p.drawPixmap(QRectF(xend, 10, 32.0, 32.0), QPixmap(fileName), source);
        fileName = getFilenameFromNumber(mines10);
        p.drawPixmap(QRectF(xend-32.0, 10, 32.0, 32.0), QPixmap(fileName), source);
    }
    else if (rows > columns)
    {
        unsigned xstart = 20 + (32*columns);
        unsigned ystart = 10;
        this->setFixedSize(30+32*(columns+1),20+32*rows);
        ui->minefieldWidget->setGeometry(10,10,32*columns,32*rows);
        ui->regenerateButton->setGeometry(xstart,ystart,31,31);
        fileName = getFilenameFromNumber(second100);
        p.drawPixmap(QRectF(xstart, ystart+ 32, 32.0, 32.0), QPixmap(fileName), source);
        fileName = getFilenameFromNumber(second10);
        p.drawPixmap(QRectF(xstart, ystart + 32*2, 32.0 , 32.0), QPixmap(fileName), source);
        fileName = getFilenameFromNumber(second1);
        p.drawPixmap(QRectF(xstart, ystart + 32*3, 32.0 , 32.0), QPixmap(fileName), source);
        fileName = getFilenameFromNumber(mines10);
        p.drawPixmap(QRectF(xstart, ystart + 32*(rows-2), 32.0, 32.0), QPixmap(fileName), source);
        fileName = getFilenameFromNumber(mines1);
        p.drawPixmap(QRectF(xstart, ystart + 32*(rows-1), 32.0, 32.0), QPixmap(fileName), source);
    }
    else
    {
        unsigned xstart = 10 + (32*(columns-1))/2;
        unsigned xend = 10 + 32*(columns-1);
        fileName = getFilenameFromNumber(second100);
        p.drawPixmap(QRectF(xstart-32.0, 10, 32.0, 32.0), QPixmap(fileName), source);
        fileName = getFilenameFromNumber(second10);
        p.drawPixmap(QRectF(xstart, 10, 32.0, 32.0), QPixmap(fileName), source);
        fileName = getFilenameFromNumber(second1);
        p.drawPixmap(QRectF(xstart+32.0, 10, 32.0, 32.0), QPixmap(fileName), source);
        fileName = getFilenameFromNumber(mines1);
        p.drawPixmap(QRectF(xend, 10, 32.0, 32.0), QPixmap(fileName), source);
        fileName = getFilenameFromNumber(mines10);
        p.drawPixmap(QRectF(xend-32.0, 10, 32.0, 32.0), QPixmap(fileName), source);
    }
}








