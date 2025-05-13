#include "analytics.h"

Analytics::Analytics(const QString& text, const QMap<QString, int>& frequency)
    : text(text), frequency(frequency) {}

int Analytics::totalWords() const {
    int total = 0;
    for (int count : frequency) {
        total += count;
    }
    return total;
}

int Analytics::uniqueWords() const {
    return frequency.size();
}

double Analytics::averageWordLength() const {
    if (frequency.isEmpty()) return 0.0;
    double totalLength = 0;
    for (auto it = frequency.constBegin(); it != frequency.constEnd(); ++it) {
        totalLength += it.key().length() * it.value();
    }
    return totalLength / totalWords();
}

QString Analytics::mostFrequentWord() const {
    QString mostFrequent;
    int maxCount = 0;
    for (auto it = frequency.constBegin(); it != frequency.constEnd(); ++it) {
        if (it.value() > maxCount) {
            maxCount = it.value();
            mostFrequent = it.key();
        }
    }
    return mostFrequent;
}
