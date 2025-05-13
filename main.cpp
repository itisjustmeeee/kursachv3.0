#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile styleFile(":/MaterialDark.qss");
        if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream styleStream(&styleFile);
            QString styleSheet = styleStream.readAll();
            a.setStyleSheet(styleSheet);
            styleFile.close();
        } else {
            QMessageBox::warning(nullptr, "Style Error", "Could not load AMOLED.qss from resources");
        }

    MainWindow w;
    w.show();
    return a.exec();
}
