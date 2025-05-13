#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "textinputwindow.h"
#include "fileinputwindow.h"
#include "instructionwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Word Frequency Analyzer");

    connect(ui->textInputButton, &QPushButton::clicked, this, &MainWindow::openTextInput);
    connect(ui->fileInputButton, &QPushButton::clicked, this, &MainWindow::openFileInput);
    connect(ui->instructionButton, &QPushButton::clicked, this, &MainWindow::openInstructions);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openTextInput() {
    try {
        TextInputWindow *textWindow = new TextInputWindow(this);
        textWindow->show();
        hide();
    } catch (const std::exception& e) {
        showError(QString("Failed to open Text Input window: %1").arg(e.what()));
    }
}

void MainWindow::openFileInput() {
    try {
        FileInputWindow *fileWindow = new FileInputWindow(this);
        fileWindow->show();
        hide();
    } catch (const std::exception& e) {
        showError(QString("Failed to open File Input window: %1").arg(e.what()));
    }
}

void MainWindow::openInstructions() {
    try {
        InstructionWindow *instructionWindow = new InstructionWindow(this);
        instructionWindow->show();
        hide();
    } catch (const std::exception& e) {
        showError(QString("Failed to open Instructions window: %1").arg(e.what()));
    }
}

void MainWindow::showError(const QString& error) {
    QMessageBox::critical(this, "Error", error);
}
