#ifndef ANALYSISWORKER_H
#define ANALYSISWORKER_H

#include <QObject>
#include <QMap>
#include "wordanalyzer.h"
#include "analytics.h"

class AnalysisWorker : public QObject {
    Q_OBJECT

public:
    explicit AnalysisWorker(QObject *parent = nullptr);

public slots:
    void analyzeText(const QString& text);
    void analyzeFile(const QString& filePath);

signals:
    void analysisFinished(const QMap<QString, int>& frequency, const Analytics& analytics);
    void errorOccurred(const QString& error);

private:
    WordAnalyzer analyzer;
};

#endif // ANALYSISWORKER_H
