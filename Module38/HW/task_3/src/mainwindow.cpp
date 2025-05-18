#include "mainwindow.h"
#include <QMainWindow>
#include <QFont>
#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QtGui/QtGui>
#include <QGraphicsPixmapItem>
#include <QDir>
#include <QPainter>
#include <QUrl>
#include <QFileDialog>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent}
{
    imageLabel = new QLabel(this);
    slider = new QSlider(Qt::Horizontal, this);
    slider->setRange(0, 10);
    openBtn = new QPushButton("Open", this);
    openBtn->setFont(QFont("Roboto", 14));

    imageLabel->setScaledContents(true);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(imageLabel);
    layout->addWidget(slider);
    layout->addWidget(openBtn);

    setMinimumSize(800, 600);

    connect(openBtn, &QPushButton::clicked, this, &MainWindow::openImage);
    connect(slider, &QSlider::valueChanged, this, &MainWindow::updateImage);
}

QPixmap MainWindow::processImage(QImage source, int radius)
{
    if (source.isNull())
        return QPixmap();

    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(QPixmap::fromImage(source));

    auto* blur = new QGraphicsBlurEffect;
    blur->setBlurRadius(radius * 10);
    item.setGraphicsEffect(blur);
    scene.addItem(&item);

    QPixmap result(source.size());
    result.fill(Qt::transparent);

    QPainter painter(&result);
    scene.render(&painter, QRectF(), QRectF(0, 0, source.width(), source.height()));

    return result;
}

void MainWindow::openImage()
{
    QString path = QFileDialog::getOpenFileName(nullptr, "Open image",
                                                QDir::homePath() + "/Downloads/",
                                                "Image files (*.png *.jpg *.jpeg)");
    if (!path.isEmpty()) {
        imagepath = path;
        originalImage = QImage(imagepath);
        updateImage(slider->value());
    }
}

void MainWindow::updateImage(int radius)
{
    if (!originalImage.isNull()) {
        imageLabel->setPixmap(processImage(originalImage, radius));
    }
}

MainWindow::~MainWindow(){};
