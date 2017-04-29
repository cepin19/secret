#include "mainwindow.h"
#include <QApplication>

#include <iostream>
int main(int argc, char *argv[])
{
    srand(unsigned(std::time(0)));

    QApplication a(argc, argv);
    MainWindow w;


    w.show();

    return a.exec();
}
