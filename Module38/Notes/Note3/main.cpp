#include <QVideoWidget>
#include <QApplication>
#include <QtGui/QtGui>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QFileDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget playerWindow;

    QVBoxLayout vbox(&playerWindow);
    QHBoxLayout buttons;

    auto videoWidget = new QVideoWidget(&playerWindow);
    vbox.addWidget(videoWidget);

    QSlider *songSlider = new QSlider(&playerWindow);
    songSlider->setOrientation(Qt::Horizontal);
    vbox.addWidget(songSlider);

    auto *openFileBtn = new QPushButton("Open", &playerWindow);
    auto *play = new QPushButton("Play", &playerWindow);
    auto *pause = new QPushButton("Pause", &playerWindow);

    buttons.addWidget(openFileBtn);
    buttons.addWidget(play);
    buttons.addWidget(pause);

    vbox.addLayout(&buttons);
    playerWindow.resize(800, 600);

    QUrl filePath;

    auto *player = new QMediaPlayer(&playerWindow);
    auto *audioOutput = new QAudioOutput(&playerWindow);
    player->setVideoOutput(videoWidget);
    player->setAudioOutput(audioOutput);

    bool isPlaying = false;

    QObject::connect(openFileBtn, &QPushButton::clicked, [&filePath, player, &isPlaying](){
        filePath = QFileDialog::getOpenFileName(nullptr, "Open media file",
                                                "C:/Users/6el0z/Downloads/",
                                                "media files (*.mp3, *.mp4)");
        player->stop();
        isPlaying = false;
    });

    QObject::connect(play, &QPushButton::clicked, [&filePath, player, &isPlaying, songSlider, &audioOutput]()
    {
        if(!isPlaying)
        {
            player->setSource(filePath);
            audioOutput->setVolume(75);

            QObject::connect(player, &QMediaPlayer::durationChanged, [songSlider](qint64 duration)
            {
                songSlider->setMinimum(0);
                songSlider->setMaximum(duration);
            });

            QObject::connect(player, &QMediaPlayer::positionChanged, [songSlider](qint64 pos)
            {
                songSlider->setValue(pos);
            });

            isPlaying = true;
        }
        player->play();
    });

    QObject::connect(songSlider, &QSlider::sliderMoved, [player, songSlider]()
    {
        player->setPosition(songSlider->value());
    });

    QObject::connect(pause, &QPushButton::clicked, player, &QMediaPlayer::pause);

    playerWindow.show();
    return a.exec();
}
