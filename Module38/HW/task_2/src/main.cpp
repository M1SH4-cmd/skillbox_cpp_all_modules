#include "mainwindow.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Redactor r;
    r.resize(800, 600);
    r.show();
    return a.exec();
}
