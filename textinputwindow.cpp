#include "textinputwindow.h"
#include "ui_textinputwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDir>

TextInputWindow::TextInputWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextInputWindow)
{
    ui->setupUi(this);
    setWindowTitle("Text Input");

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

    connect(ui->analyzeButton, &QPushButton::clicked, this, &TextInputWindow::startAnalysis);
    connect(ui->exportButton, &QPushButton::clicked, this, &TextInputWindow::exportResults);
    connect(ui->clearCacheButton, &QPushButton::clicked, this, &TextInputWindow::clearCache);
    connect(ui->backButton, &QPushButton::clicked, this, &TextInputWindow::backToMainWindow);
    connect(worker, &AnalysisWorker::analysisFinished, this, &TextInputWindow::handleAnalysisResult);
    connect(worker, &AnalysisWorker::errorOccurred, this, &TextInputWindow::handleError);
}

TextInputWindow::~TextInputWindow()
{
    workerThread->quit();
    workerThread->wait();
    delete worker;
    delete wordGraph;
    delete scene;
    delete ui;
}

void TextInputWindow::wheelEvent(QWheelEvent *event){
    qreal scaleFactor = event->angleDelta().y() > 0 ? 1.1 : 0.9;
    ui->graphicsView->scale(scaleFactor, scaleFactor);
}

void TextInputWindow::startAnalysis() {
    QString text = ui->inputTextEdit->toPlainText();
    QString cacheKey = QString::number(qHash(text));

    QMap<QString, int> frequency;
    Analytics analytics("", {});
    if (cache.retrieve(cacheKey, frequency, analytics)) {
        handleAnalysisResult(frequency, analytics);
        return;
    }

    ui->resultTextEdit->clear();
    scene->clear();
    QMetaObject::invokeMethod(worker, [=] { worker->analyzeText(text); });
}

void TextInputWindow::handleAnalysisResult(const QMap<QString, int>& freq, const Analytics& anal) {
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

    QString cacheKey = QString::number(qHash(ui->inputTextEdit->toPlainText()));
    cache.store(cacheKey, frequency, analytics);
}

void TextInputWindow::handleError(const QString& error) {
    showError(error);
}

void TextInputWindow::exportResults() {
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

void TextInputWindow::clearCache() {
    cache.clear();
    ui->resultTextEdit->clear();
    scene->clear();
    showError("Cache cleared.");
}

void TextInputWindow::backToMainWindow() {
    parentWidget()->show();
    close();
}

void TextInputWindow::showError(const QString& error) {
    QMessageBox::critical(this, "Error", error);
}
