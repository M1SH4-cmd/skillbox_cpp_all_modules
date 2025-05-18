#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPixmap>
#include <QPushButton>
#include <QSlider>
#include <QLabel>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QPixmap processImage(QImage source, int radius);
    void openImage();
    void updateImage(int radius);

private:
    QString imagepath;
    QImage originalImage;
    QLabel *imageLabel;
    QSlider *slider;
    QPushButton *openBtn;
};

#endif // MAINWINDOW_H
