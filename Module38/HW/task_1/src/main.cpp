#include "soundButton.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;
    w.setFixedSize(300, 300);
    SoundButton btn(&w);
    w.show();
    return a.exec();
}
