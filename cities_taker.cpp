#include <iostream>

#include <QDebug>

#include "taker.hpp"

using namespace cities;

namespace {
    const QString base_url = 
        "http://api.geonames.org/search?name_startsWith=%1&maxRows=%2&featureCode=PPL&username=%3";
    const QString username = "gooddocteur";
}



Taker::Taker() { 
    connect(&data_access, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(done(QNetworkReply*)));
}

Taker* Taker::take(const QString& city) { 
    qDebug() << "take the " << city;
    read_data(form_url(city));
    return this;
}

QUrl Taker::form_url(const QString& city) {
    return QUrl(base_url.arg(city).arg(5).arg(username));
}

void Taker::read_data(const QUrl& city) {
    qDebug() << "read_data " << city.toString();
    data_access.get(QNetworkRequest(city));
}

void Taker::done(QNetworkReply* reply) {
    QDomDocument document;
    document.setContent(reply);
    emit give_back(document);
}
