#include "instructionwindow.h"
#include "ui_instructionwindow.h"
#include <QMessageBox>

InstructionWindow::InstructionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InstructionWindow)
{
    try {
        ui->setupUi(this);
        setWindowTitle("Instructions");

        ui->instructionTextEdit->setReadOnly(true);
        ui->instructionTextEdit->setText(
            "Instructions:\n"
            "1. Use 'Enter Text' to input text manually and analyze word frequency.\n"
            "2. Use 'Select File' to load a .txt file for analysis.\n"
            "3. Results include word frequencies, analytics, and a text-based graph.\n"
            "4. Export results to .txt or .csv using the Export button.\n"
            "5. Clear cache to reset stored results."
        );

        connect(ui->backButton, &QPushButton::clicked, this, &InstructionWindow::backToMainWindow);
    } catch (const std::exception& e) {
        showError(QString("Failed to initialize Instructions window: %1").arg(e.what()));
    }
}

InstructionWindow::~InstructionWindow()
{
    delete ui;
}

void InstructionWindow::backToMainWindow() {
    parentWidget()->show();
    close();
}

void InstructionWindow::showError(const QString& error) {
    QMessageBox::critical(this, "Error", error);
}
