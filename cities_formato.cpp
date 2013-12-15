#include <QDebug>
#include <cassert>

#include "formato.hpp"

using namespace cities;

Formato::Formato() { }

Formato* Formato::format(const QDomDocument& data) {
    QStringList cities;

    QDomNodeList elements = data.elementsByTagName("geoname");
    for (int i = 0; i < elements.size(); i++) {
        assert(elements.at(i).toElement().elementsByTagName("name").size() > 0);
        QString city = elements.at(i).toElement().elementsByTagName("name").at(0).toElement().text();
        if (!cities.contains(city))
            cities.push_back(city);
    }

    emit done(cities);

    return this;
}
