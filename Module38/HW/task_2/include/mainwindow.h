#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QWebEngineView>

class Redactor : public QMainWindow
{
    Q_OBJECT

public:
    Redactor(QWidget *parent = nullptr);
    ~Redactor();

private:
    QVBoxLayout *layout;
    QPlainTextEdit *htmlRed;
    QWebEngineView *htmlViewer;
};
#endif // MAINWINDOW_H
