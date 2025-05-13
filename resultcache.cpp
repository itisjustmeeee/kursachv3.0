#include "resultcache.h"

ResultCache::ResultCache() {}

void ResultCache::store(const QString& key, const QMap<QString, int>& frequency, const Analytics& analytics) {
    cache.insert(key, QPair<QMap<QString, int>, Analytics>(frequency, analytics));
}

bool ResultCache::retrieve(const QString& key, QMap<QString, int>& frequency, Analytics& analytics) {
    if (cache.contains(key)) {
        frequency = cache[key].first;
        analytics = cache[key].second;
        return true;
    }
    return false;
}

void ResultCache::clear() {
    cache.clear();
}
