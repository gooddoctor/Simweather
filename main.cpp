#include <QApplication>

#include <iostream>

#include "taker.hpp"
#include "formato.hpp"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    Taker taker;
    Formato formatter;
    QObject::connect(&taker, SIGNAL(give_back(const QDomDocument&)),
                     &formatter, SLOT(format(const QDomDocument)));
    taker.take("Kerch");
    return app.exec();
}
