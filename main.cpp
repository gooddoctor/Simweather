#include <QApplication>

#include <iostream>

#include "taker.hpp"
#include "formato.hpp"
#include "view.hpp"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    weather::Taker weather_taker;
    cities::Taker cities_taker;

    weather::Formato weather_formato;
    cities::Formato cities_formato;

    View view;

    QObject::connect(&view, SIGNAL(desire_weather(const QString&)),
                     &weather_taker, SLOT(take(const QString&)));
    QObject::connect(&view, SIGNAL(desire_cities(const QString&)),
                     &cities_taker, SLOT(take(const QString&)));

    QObject::connect(&weather_taker, SIGNAL(give_back(const QDomDocument&)),
                     &weather_formato, SLOT(format(const QDomDocument)));
    QObject::connect(&cities_taker, SIGNAL(give_back(const QDomDocument&)),
                     &cities_formato, SLOT(format(const QDomDocument)));

    QObject::connect(&weather_formato, SIGNAL(done(const QString&)),
                     &view, SLOT(satisfy_weather(const QString&)));
    QObject::connect(&weather_formato, SIGNAL(shit_happens()),
                     &view, SLOT(damn()));

    QObject::connect(&cities_formato, SIGNAL(done(const QStringList&)),
                     &view, SLOT(satisfy_cities(const QStringList&)));

    view.show();

    return app.exec();
}
