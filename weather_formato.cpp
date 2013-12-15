#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <iostream>
#include <cassert>

#include "formato.hpp"

using namespace weather;

Formato::Formato() { }

Formato* Formato::format(const QDomDocument& data) {
    //check the data
    if (!check(data)) {
        emit shit_happens();
        return this;
    }

    //fill the map
    parse(data);

    //the next code is all about create html page
    QFile file(":resources/template.html");
    assert(file.open(QIODevice::ReadOnly | QIODevice::Text));
    
    assert(info.find("city") != info.end());
    assert(info.find("date") != info.end());
    assert(info.find("icon") != info.end());
    assert(info.find("desc") != info.end());
    assert(info.find("temp") != info.end());

    QString html = QTextStream(&file).readAll().
        arg(info["city"]).
        arg(info["date"]).
        arg(info["icon"]).
        arg(info["desc"]).
        arg(info["temp"]);

    //fire it up
    emit done(html);

    return this;
}

void Formato::parse(const QDomDocument& data) {
    assert(data.elementsByTagName("query").size() > 0);
    assert(data.elementsByTagName("current_condition").size() > 0);
    assert(data.elementsByTagName("current_condition").at(0).toElement().
           elementsByTagName("temp_C").size() > 0);
    assert(data.elementsByTagName("current_condition").at(0).toElement().
           elementsByTagName("weatherIconUrl").size() > 0);
    assert(data.elementsByTagName("current_condition").at(0).toElement().
           elementsByTagName("weatherDesc").size() > 0);

    info.clear();

    info.insert({"city", data.elementsByTagName("query").at(0).toElement().text()});
    info.insert({"temp", data.elementsByTagName("current_condition").at(0).toElement().
                elementsByTagName("temp_C").at(0).toElement().text()});
    info.insert({"temp", data.elementsByTagName("current_condition").at(0).toElement().
                elementsByTagName("temp_C").at(0).toElement().text()});
    info.insert({"icon", data.elementsByTagName("current_condition").at(0).toElement().
                elementsByTagName("weatherIconUrl").at(0).firstChild().toCDATASection().data()});
    info.insert({"desc", data.elementsByTagName("current_condition").at(0).toElement().
                elementsByTagName("weatherDesc").at(0).firstChild().toCDATASection().data()});
    info.insert({"date", 
                QString("%1.%2").
                arg(QDateTime::currentDateTime().date().day(), 2, 10, QChar('0')).
                arg(QDateTime::currentDateTime().date().month(), 2, 10, QChar('0'))});
}

bool Formato::check(const QDomDocument& data) {
    if (data.elementsByTagName("query").isEmpty() ||
        data.elementsByTagName("current_condition").isEmpty() || 
        (data.elementsByTagName("current_condition").at(0).toElement().
         elementsByTagName("temp_C").isEmpty()) ||
        (data.elementsByTagName("current_condition").at(0).toElement().
         elementsByTagName("weatherIconUrl").isEmpty()) ||
        (data.elementsByTagName("current_condition").at(0).toElement().
         elementsByTagName("weatherDesc").isEmpty()))
        return false;
    return true;
}

