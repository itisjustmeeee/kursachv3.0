#ifndef TEXTINPUTWINDOW_H
#define TEXTINPUTWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QGraphicsScene>
#include <QWheelEvent>
#include "analysisworker.h"
#include "resultcache.h"
#include "wordgraph.h"

namespace Ui {
class TextInputWindow;
}

class TextInputWindow : public QMainWindow
{
    Q_OBJECT

public:
    TextInputWindow(QWidget *parent = nullptr);
    ~TextInputWindow();

protected:
    void wheelEvent(QWheelEvent* event) override;

private slots:
    void startAnalysis();
    void handleAnalysisResult(const QMap<QString, int>& frequency, const Analytics& analytics);
    void handleError(const QString& error);
    void exportResults();
    void clearCache();
    void backToMainWindow();

private:
    void showError(const QString& error);

    Ui::TextInputWindow *ui;
    QThread *workerThread;
    AnalysisWorker *worker;
    ResultCache cache;
    QGraphicsScene *scene;
    WordGraph *wordGraph;
    QMap<QString, int> frequency;
    Analytics analytics;

};

#endif // TEXTINPUTWINDOW_H
