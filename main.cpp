#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Database db;
    db.createconnect();
    MainWindow w;

    QFile file(":/new/prefix1/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet { QLatin1String(file.readAll()) };
    a.setStyleSheet(styleSheet);
    w.show();
    return a.exec();
}
