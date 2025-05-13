#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openTextInput();
    void openFileInput();
    void openInstructions();

private:
    void showError(const QString& error);

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
