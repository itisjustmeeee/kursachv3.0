#ifndef INSTRUCTIONWINDOW_H
#define INSTRUCTIONWINDOW_H

#include <QMainWindow>

namespace Ui {
class InstructionWindow;
}

class InstructionWindow : public QMainWindow
{
    Q_OBJECT

public:
    InstructionWindow(QWidget *parent = nullptr);
    ~InstructionWindow();

private slots:
    void backToMainWindow();

private:
    void showError(const QString& error);

    Ui::InstructionWindow *ui;
};

#endif // INSTRUCTIONWINDOW_H
