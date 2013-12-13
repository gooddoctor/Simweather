#include <iostream>

#include <QDebug>

#include "taker.hpp"

const QString base_url = 
    "http://api.worldweatheronline.com/free/v1/weather.ashx?q=%1&format=%2&num_of_days=%3&key=%4";
const QString key = "nxbzr35722s7yjpaexbbu27h";


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
    qDebug() << "form url " << city;
    return QUrl(base_url.arg(city).arg("xml").arg(5).arg(key));
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


