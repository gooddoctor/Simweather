#ifndef __VIEW_H
#define __VIEW_H

#include <QMainWindow>
#include <QWebView>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QStringListModel>

class View : public QMainWindow { Q_OBJECT
public:
    View();
public slots:
    View* satisfy_weather(const QString& data);
    View* satisfy_cities(const QStringList& data);
    View* damn();
private:
    void place_it();
    void animate_it(QWidget* widget);
private slots:
    void go_handler();
    void text_handler(const QString& city);
private:
    QLineEdit* search;
    QPushButton* go;

    QStackedWidget* info;
    QWebView* no_data;
    QWebView* weather;

    QStringListModel* cities;
signals:
    void desire_weather(const QString& city);
    void desire_cities(const QString& city);
};

#endif
