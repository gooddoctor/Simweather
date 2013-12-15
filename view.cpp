#include <QFile>
#include <QTextStream>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <iostream>
#include <cassert>

#include "view.hpp"

View::View() {
    search = new QLineEdit();

    go = new QPushButton(tr("Поиск"));
    connect(go, SIGNAL(clicked()), this, SLOT(go_handler()));

    // the next code is all about initializing stack of widgets
    QFile file(":resources/no_data.html");
    assert(file.open(QIODevice::ReadOnly | QIODevice::Text));

    no_data = new QWebView();
    no_data->setHtml(QTextStream(&file).readAll());

    weather = new QWebView();

    info = new QStackedWidget();
    info->addWidget(no_data);
    info->addWidget(weather);
    info->setCurrentIndex(0);

    place_it();
}

View* View::satisfy(const QString& data) {
    std::cout << qPrintable(data) << std::endl;
    weather->setHtml(data);
    info->setCurrentIndex(1);
    return this;
}

View* View::damn() {
    info->setCurrentIndex(0);
    return this;
}

void View::place_it() {
    QHBoxLayout* horizontal = new QHBoxLayout();
    horizontal->addWidget(search);
    horizontal->addWidget(go);

    QVBoxLayout* vertical = new QVBoxLayout();
    vertical->addLayout(horizontal);
    vertical->addWidget(info);

    QWidget* content = new QWidget();
    content->setLayout(vertical);

    setCentralWidget(content);
    resize(600, 200);
}

void View::go_handler() {
    if (search->text().trimmed().length() > 0)
        emit desire(search->text().trimmed());
}
