#ifndef __TAKER_H
#define __TAKER_H

#include <QApplication>
#include <QUrl>
#include <QNetworkReply>
#include <QDomDocument>

class Taker : public QObject { Q_OBJECT
public:
    Taker();
public slots:
    Taker* take(const QString& city);
private:
    QUrl form_url(const QString& city);
    void read_data(const QUrl& city);
private:
    QNetworkAccessManager data_access;
private slots:
    void done(QNetworkReply* reply);
signals:
    void give_back(const QDomDocument& document);
};

#endif
