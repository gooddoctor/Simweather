#ifndef __VIEW_H
#define __VIEW_H

#include <QMainWindow>
#include <QWebView>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>


class View : public QMainWindow { Q_OBJECT
public:
    View();
public slots:
    View* satisfy(const QString& data);
    View* damn();
private:
    void place_it();
private slots:
    void go_handler();
private:
    QLineEdit* search;
    QPushButton* go;

    QStackedWidget* info;
    QWebView* no_data;
    QWebView* weather;
signals:
    void desire(const QString& city);
};

#endif
