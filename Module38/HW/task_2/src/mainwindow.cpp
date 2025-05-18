#include "mainwindow.h"
#include <QSizePolicy>

Redactor::Redactor(QWidget *parent)
    : QMainWindow(parent)
{
    QString defaultHtml = R"(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Тест редактора</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            line-height: 1.6;
            margin: 20px;
            color: #333;
        }
        h1 {
            color: #2c3e50;
            border-bottom: 2px solid #3498db;
            padding-bottom: 5px;
        }
        .container {
            max-width: 800px;
            margin: 0 auto;
        }
        img {
            max-width: 100%;
            height: auto;
            border: 1px solid #ddd;
            border-radius: 4px;
            padding: 5px;
        }
        table {
            border-collapse: collapse;
            width: 100%;
            margin: 20px 0;
        }
        th, td {
            border: 1px solid #ddd;
            padding: 8px;
            text-align: left;
        }
        th {
            background-color: #f2f2f2;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Добро пожаловать в HTML-редактор</h1>

        <p>Это тестовая страница для проверки работы вашего редактора.</p>

        <h2>Основные элементы HTML</h2>

        <p>Пример <strong>жирного</strong> и <em>курсивного</em> текста.</p>

        <p>Ссылка: <a href="https://www.google.com" target="_blank">Google</a></p>

        <h3>Изображение</h3>
        <img src="https://via.placeholder.com/400x200" alt="Пример изображения">

        <h3>Таблица</h3>
        <table>
            <tr>
                <th>Заголовок 1</th>
                <th>Заголовок 2</th>
                <th>Заголовок 3</th>
            </tr>
            <tr>
                <td>Ячейка 1</td>
                <td>Ячейка 2</td>
                <td>Ячейка 3</td>
            </tr>
            <tr>
                <td>Ячейка 4</td>
                <td>Ячейка 5</td>
                <td>Ячейка 6</td>
            </tr>
        </table>

        <h3>Список</h3>
        <ul>
            <li>Элемент списка 1</li>
            <li>Элемент списка 2</li>
            <li>Элемент списка 3</li>
        </ul>
    </div>
</body>
</html>
    )";

    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    layout = new QHBoxLayout(centralWidget);

    htmlRed = new QPlainTextEdit(centralWidget);
    htmlViewer = new QWebEngineView(centralWidget);

    htmlRed->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    htmlViewer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    htmlRed->setMinimumSize(300, 300);
    htmlViewer->setMinimumSize(300, 300);

    layout->addWidget(htmlRed);
    layout->addWidget(htmlViewer);
    htmlRed->setPlainText(defaultHtml);
    htmlRed->setFont(QFont("Roboto", 14));

    htmlViewer->setHtml(htmlRed->toPlainText());

    QObject::connect(htmlRed, &QPlainTextEdit::textChanged, [this]() {
        htmlViewer->setHtml(htmlRed->toPlainText());
    });
}

Redactor::~Redactor() {}
