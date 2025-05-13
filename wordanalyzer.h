#ifndef WORDANALYZER_H
#define WORDANALYZER_H

#include <QString>
#include <QMap>

class WordAnalyzer {
public:
    WordAnalyzer();
    QMap<QString, int> analyze(const QString& text);
};

#endif // WORDANALYZER_H
