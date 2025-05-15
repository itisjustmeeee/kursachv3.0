#ifndef ANALYTICS_H
#define ANALYTICS_H

#include <QString>
#include <QMap>

class Analytics {
public:
    Analytics() = default;
    Analytics(const QString& text, const QMap<QString, int>& frequency);
    int totalWords() const;
    int uniqueWords() const;
    double averageWordLength() const;
    QString mostFrequentWord() const;

private:
    QString text;
    QMap<QString, int> frequency;
};

#endif // ANALYTICS_H
