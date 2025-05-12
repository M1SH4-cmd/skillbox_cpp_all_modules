#include "soundButton.h"
#include <iostream>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QDir>

SoundButton::SoundButton(QWidget *parent) {
    setParent(parent);
    setToolTip("Stop");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    mButtonUpPixmap = QPixmap(":/images/images/REDbtn.png");
    mButtonDownPixmap = QPixmap(":/images/images/BLUEbtn.png");

    if (mButtonUpPixmap.isNull() || mButtonDownPixmap.isNull()) {
        std::cerr << "Failed to load button images!" << std::endl;
        return;
    }

    mCurrentButtonPixmap = mButtonUpPixmap;
    setGeometry(mCurrentButtonPixmap.rect());
    connect(this, &QPushButton::clicked, this, &SoundButton::setDown);

    auto *player = new QMediaPlayer(parent);
    auto *audioOutput = new QAudioOutput(parent);
    player->setAudioOutput(audioOutput);
    QDir pathToSounds = QDir::current();
    pathToSounds.setPath(pathToSounds.absolutePath());

    QObject::connect(this, &QPushButton::clicked, [player, audioOutput, pathToSounds](){
        player->setSource(QUrl("qrc:/sounds/sounds/sound2.mp3"));
        audioOutput->setVolume(64);
        player->play();
    });
}

void SoundButton::paintEvent(QPaintEvent *e) {
    QPainter p(this);
    p.drawPixmap(e->rect(), mCurrentButtonPixmap);
}

QSize SoundButton::sizeHint() const {
    return QSize(100, 100);
}

QSize SoundButton::minimumSizeHint() const {
    return sizeHint();
}

void SoundButton::keyPressEvent(QKeyEvent *e) {
    setDown();
    QPushButton::keyPressEvent(e);
}

void SoundButton::setDown() {
    mCurrentButtonPixmap = mButtonDownPixmap;
    update();
    QTimer::singleShot(100, this, &SoundButton::setUp);
}

void SoundButton::setUp() {
    mCurrentButtonPixmap = mButtonUpPixmap;
    update();
}
