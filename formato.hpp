#ifndef __FORMATO_H
#define __FORMATO_H

#include <QApplication>
#include <QDomDocument>
#include <QStringList>

#include <map>

namespace weather {
    class Formato : public QObject { Q_OBJECT
    public:
        Formato();
    public slots:
        Formato* format(const QDomDocument& data);
    private:
        void parse(const QDomDocument& data);
        bool check(const QDomDocument& data);
    private:
        std::map<QString, QString> info;
    signals:
        void done(const QString& data);
        void shit_happens();
    };
}

namespace cities {
    class Formato : public QObject { Q_OBJECT
    public:
        Formato();
    public slots:
        Formato* format(const QDomDocument& data);
    signals:
        void done(const QStringList& data);
    };
}
#endif

