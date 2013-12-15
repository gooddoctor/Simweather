#include <QApplication>

#include <iostream>

#include "taker.hpp"
#include "formato.hpp"
#include "view.hpp"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    Taker taker;
    Formato formato;
    View view;

    QObject::connect(&view, SIGNAL(desire(const QString&)),
                     &taker, SLOT(take(const QString&)));
    QObject::connect(&taker, SIGNAL(give_back(const QDomDocument&)),
                     &formato, SLOT(format(const QDomDocument)));
    QObject::connect(&formato, SIGNAL(done(const QString&)),
                     &view, SLOT(satisfy(const QString&)));

    view.show();

    return app.exec();
}
