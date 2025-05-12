#include "mainwindow.h"

Redactor::Redactor(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *mainW(parent);

    htmlRed = new QPlainTextEdit();
    htmlViewer = new QWebEngineView();

    layout->addWidget(htmlRed);
    layout->addWidget(htmlViewer);
    mainW->setLayout(layout);

    QObject::connect(htmlRed, &QPlainTextEdit::textChanged, [this](){
        htmlViewer->setHtml(htmlRed->toPlainText());
    });
}
Redactor::~Redactor() {}
