#include <QFile>
#include <QTextStream>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <cassert>

#include "view.hpp"

View::View() {
    search = new QLineEdit();
    go = new QPushButton(tr("Поиск"));

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
}
