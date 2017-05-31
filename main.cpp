#include "mainwindow.h"
#include <QApplication>
#include"game.h"
#include"startwindow.h"
#include<fstream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(NULL));

    StartWindow sw;

    return a.exec();
}
