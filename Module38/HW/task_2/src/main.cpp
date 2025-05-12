#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Redactor r;
    r.resize(1920, 1080);
    r.show();
    return a.exec();
}
