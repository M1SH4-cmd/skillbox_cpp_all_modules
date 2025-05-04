#include <iostream>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QApplication>
#include <QtGui/QtGui>
#include <QGraphicsPixmapItem>
#include <QDir>
#include <QPainter>

QImage blurImage(QImage source)
{
    if(source.isNull()) return QImage();
    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(QPixmap::fromImage(source));

    auto* blur = new QGraphicsBlurEffect;
    blur->setBlurRadius(8);
    item.setGraphicsEffect(blur);
    scene.addItem(&item);
    QImage result(source.size(), QImage::Format_ARGB32);
    result.fill(Qt::transparent);
    QPainter painter(&result);
    scene.render(&painter, QRectF(), QRectF(0, 0, source.width(), source.height()));
    return result;
}

void processSingleImage(QString sourceFile, QString destFile) {
    auto blured = blurImage(QImage(sourceFile));
    blured.save(destFile);
}

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QDir sourceDir("./images/not_blured");
    QDir destDir("./images/blured");
    auto images = sourceDir.entryList(QStringList() << "*.png" << "*.PNG" << "*.jpg" << "*.JPG", QDir::Files);
    QElapsedTimer timer;
    timer.start();
    for (auto &filename : images) {
        processSingleImage(sourceDir.path() + "/" + filename, destDir.path()+ "/" + "blured_" + filename);
    }
    std::cout << "Calc time:\t" << timer.elapsed() << " ms" << std::endl;
    return app.exec();
}
