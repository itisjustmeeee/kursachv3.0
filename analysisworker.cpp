#include "analysisworker.h"
#include <QFile>
#include <QTextStream>

AnalysisWorker::AnalysisWorker(QObject *parent) : QObject(parent) {}

void AnalysisWorker::analyzeText(const QString& text) {
    if (text.isEmpty()) {
        emit errorOccurred("Input text is empty!");
        return;
    }

    QMap<QString, int> frequency = analyzer.analyze(text);
    Analytics analytics(text, frequency);
    emit analysisFinished(frequency, analytics);
}

void AnalysisWorker::analyzeFile(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit errorOccurred("Could not open file: " + filePath);
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    if (content.isEmpty()) {
        emit errorOccurred("File is empty: " + filePath);
        return;
    }

    QMap<QString, int> frequency = analyzer.analyze(content);
    Analytics analytics(content, frequency);
    emit analysisFinished(frequency, analytics);
}
