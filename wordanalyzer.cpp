#include "wordanalyzer.h"

#include <QRegularExpression>

WordAnalyzer::WordAnalyzer() {}

QMap<QString, int> WordAnalyzer::analyze(const QString& text) {
    QMap<QString, int> frequency;
    QRegularExpression wordRegex("[\\p{L}]+");
    QRegularExpressionMatchIterator it = wordRegex.globalMatch(text.toLower());
    while (it.hasNext()) {
        QString word = it.next().captured();
        frequency[word]++;
    }
    return frequency;
}
