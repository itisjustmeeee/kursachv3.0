#ifndef FILEINPUTWINDOW_H
#define FILEINPUTWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QWheelEvent>
#include "analysisworker.h"
#include <QGraphicsScene>
#include "resultcache.h"
#include "wordgraph.h"

namespace Ui {
class FileInputWindow;
}

class FileInputWindow : public QMainWindow
{
    Q_OBJECT

public:
    FileInputWindow(QWidget *parent = nullptr);
    ~FileInputWindow();

protected:
    void wheelEvent(QWheelEvent* event) override;

private slots:
    void selectAndAnalyze();
    void handleAnalysisResult(const QMap<QString, int>& frequency, const Analytics& analytics);
    void handleError(const QString& error);
    void exportResults();
    void clearCache();
    void backToMainWindow();

private:
    void showError(const QString& error);

    Ui::FileInputWindow *ui;
    QThread *workerThread;
    AnalysisWorker *worker;
    ResultCache cache;
    QString filePath;
    QGraphicsScene *scene;
    WordGraph *wordGraph;
    QMap<QString, int> frequency;
    Analytics analytics;
};

#endif // FILEINPUTWINDOW_H
