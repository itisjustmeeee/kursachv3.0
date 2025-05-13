#ifndef RESULTCACHE_H
#define RESULTCACHE_H

#include <QMap>
#include <QString>
#include "analytics.h"

class ResultCache {
public:
    ResultCache();
    void store(const QString& key, const QMap<QString, int>& frequency, const Analytics& analytics);
    bool retrieve(const QString& key, QMap<QString, int>& frequency, Analytics& analytics);
    void clear();

private:
    QMap<QString, QPair<QMap<QString, int>, Analytics>> cache;
};

#endif // RESULTCACHE_H
