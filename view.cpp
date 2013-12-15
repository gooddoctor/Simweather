#include <QFile>
#include <QTextStream>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

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
    no_data->setGraphicsEffect([]() {
            QGraphicsOpacityEffect* no_data_opacity = new QGraphicsOpacityEffect();
            no_data_opacity->setOpacity(1.0);
            return no_data_opacity;
        }());

    weather = new QWebView();
    weather->setGraphicsEffect([]() {
            QGraphicsOpacityEffect* weather_opacity = new QGraphicsOpacityEffect();
            weather_opacity->setOpacity(1.0);
            return weather_opacity;
        }());

    info = new QStackedWidget();
    info->addWidget(no_data);
    info->addWidget(weather);
    info->setCurrentIndex(0);

    place_it();
}

View* View::satisfy(const QString& data) {
    //show weather
    weather->setHtml(data);
    info->setCurrentWidget(weather);
    //slighty animated
    animate_it(weather);

    return this;
}

View* View::damn() {
    //show damn
    info->setCurrentWidget(no_data);
    //slighty animated
    animate_it(no_data);

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

void View::animate_it(QWidget* widget) {
    QGraphicsOpacityEffect* effect = static_cast<QGraphicsOpacityEffect*>(widget->graphicsEffect());
    QPropertyAnimation* animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(1000);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void View::go_handler() {
    if (search->text().trimmed().length() > 0)
        emit desire(search->text().trimmed());
}
