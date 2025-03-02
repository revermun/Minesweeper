#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeMinesSpinBoxBorders()
{
    int rows = ui->rowSpinBox->value();
    int columns = ui->columnSpinBox->value();
    int cellsTotal = rows*columns;
    int minesMinimum = int(cellsTotal*0.1);
    int minesMaximum = int(cellsTotal*0.3);
    ui->minesSpinBox->setMinimum(minesMinimum);
    ui->minesSpinBox->setMaximum(minesMaximum);
}

void MainWindow::startGame()
{

    this->close();
    game.rows = ui->rowSpinBox->value();
    game.columns = ui->columnSpinBox->value();
    game.minesCount = ui->minesSpinBox->value();
    game.show();

}
