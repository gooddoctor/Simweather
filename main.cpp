#include <QApplication>

#include <iostream>

#include "taker.hpp"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    Taker taker;
    taker.take("Kerch");
    return app.exec();
}
