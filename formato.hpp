#ifndef __FORMATO_H
#define __FORMATO_H

#include <QApplication>
#include <QDomDocument>

class Formato : public QObject { Q_OBJECT
public:
    Formato();
public slots:
    Formato* format(const QDomDocument& data);
};

#endif
