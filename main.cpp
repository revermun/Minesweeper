#include "mainwindow.h"
#include "minefield.h"

#include <QApplication>
#include <random>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
