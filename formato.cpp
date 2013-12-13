#include <QDebug>
#include <QFile>
#include <iostream>

#include "formato.hpp"

Formato::Formato() { }

Formato* Formato::format(const QDomDocument& data) {
    QFile file(":resources/template.html");
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         qFatal("ooops. Program is corrupt");

     QTextStream in_stream(&file);
     while (!in_stream.atEnd()) {
         std::cout << in_stream.readLine().toUtf8().data() << std::endl;
     }

    return this;
}

