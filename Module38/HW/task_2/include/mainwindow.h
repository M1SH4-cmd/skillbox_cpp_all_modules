#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QWebEngineView>

class Redactor : public QMainWindow
{
    Q_OBJECT

public:
    Redactor(QWidget *parent = nullptr);
    ~Redactor();

private:
    QHBoxLayout *layout;
    QPlainTextEdit *htmlRed;
    QWebEngineView *htmlViewer;
};
#endif // MAINWINDOW_H
