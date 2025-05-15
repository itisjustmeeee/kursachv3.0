#include "fileinputwindow.h"
#include "ui_fileinputwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

FileInputWindow::FileInputWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FileInputWindow)
{
    ui->setupUi(this);
    setWindowTitle("File Input");

    workerThread = new QThread(this);
    worker = new AnalysisWorker();
    worker->moveToThread(workerThread);
    workerThread->start();

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    wordGraph = new WordGraph();

    connect(ui->selectAndAnalyzeButton, &QPushButton::clicked, this, &FileInputWindow::selectAndAnalyze);
    connect(ui->exportButton, &QPushButton::clicked, this, &FileInputWindow::exportResults);
    connect(ui->clearCacheButton, &QPushButton::clicked, this, &FileInputWindow::clearCache);
    connect(ui->backButton, &QPushButton::clicked, this, &FileInputWindow::backToMainWindow);
    connect(worker, &AnalysisWorker::analysisFinished, this, &FileInputWindow::handleAnalysisResult);
    connect(worker, &AnalysisWorker::errorOccurred, this, &FileInputWindow::handleError);
}

FileInputWindow::~FileInputWindow()
{
    workerThread->quit();
    workerThread->wait();
    delete worker;
    delete wordGraph;
    delete scene;
    delete ui;
}

void FileInputWindow::wheelEvent(QWheelEvent *event){
    qreal scaleFactor = event->angleDelta().y() > 0 ? 1.1 : 0.9;
    ui->graphicsView->scale(scaleFactor, scaleFactor);
}

void FileInputWindow::selectAndAnalyze() {
    filePath = QFileDialog::getOpenFileName(this, "Select Text File", "", "Text Files (*.txt)");
    if (filePath.isEmpty()) {
        return;
    }

    QString cacheKey = QString::number(qHash(filePath));
    QMap<QString, int> frequency;
    Analytics analytics("", {});
    if (ResultCache::instance().retrieve(cacheKey, frequency, analytics)) {
        handleAnalysisResult(frequency, analytics);
        return;
    }

    ui->resultTextEdit->clear();
    scene->clear();
    QMetaObject::invokeMethod(worker, [=] { worker->analyzeFile(filePath); });
}

void FileInputWindow::handleAnalysisResult(const QMap<QString, int>& freq, const Analytics& anal) {
    frequency = freq;
    analytics = anal;

    QString result;
    result += QString("Total Words: %1\n").arg(analytics.totalWords());
    result += QString("Unique Words: %1\n").arg(analytics.uniqueWords());
    result += QString("Average Word Length: %1\n").arg(analytics.averageWordLength(), 0, 'f', 2);
    result += QString("Most Frequent Word: %1\n").arg(analytics.mostFrequentWord());
    result += "\nWord Frequencies:\n";
    for (auto it = frequency.constBegin(); it != frequency.constEnd(); ++it) {
        result += QString("%1: %2\n").arg(it.key()).arg(it.value());
    }

    ui->resultTextEdit->setText(result);

    scene->clear();
    wordGraph->drawLineGraph(frequency, scene);

    QString cacheKey = QString::number(qHash(filePath));
    ResultCache::instance().store(cacheKey, frequency, analytics);
}

void FileInputWindow::handleError(const QString& error) {
    showError(error);
}

void FileInputWindow::exportResults() {
    QString filePath = QFileDialog::getSaveFileName(this, "Export Results", "", "Text Files (*.txt);;CSV Files (*.csv)");
    if (filePath.isEmpty()) return;

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        showError("Could not save file!");
        return;
    }

    QTextStream out(&file);
    if (filePath.endsWith(".csv")){
        out << "Word,Frequency\n";
        for (auto it = frequency.constBegin(); it != frequency.constEnd(); ++it){
            out << "\"" << it.key() << "\"," << it.value() << "\n";
        }
    } else {
        out << "Analytics:\n";
        out << "Total Words: " << analytics.totalWords() << "\n";
        out << "Unique Words: " << analytics.uniqueWords() << "\n";
        out << "Average Word Length: " << analytics.averageWordLength() << "\n";
        out << "Most Frequent Word: " << analytics.mostFrequentWord() << "\n";
        out << "\nWord Frequencies:\n";
        for (auto it = frequency.constBegin(); it != frequency.constEnd(); ++it){
            out << it.key() << ": " << it.value() << "\n";
        }
    }
    file.close();
}

void FileInputWindow::clearCache() {
    ResultCache::instance().clear();
    ui->resultTextEdit->clear();
    scene->clear();
    showError("Cache cleared.");
}

void FileInputWindow::backToMainWindow() {
    parentWidget()->show();
    close();
}

void FileInputWindow::showError(const QString& error) {
    QMessageBox::critical(this, "Error", error);
}
