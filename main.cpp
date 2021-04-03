#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
   Connection c;
    bool test=c.createconnection();
    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        QFile File("C:/Users/user/Desktop/reservation/SyNet.qss");
        File.open(QFile::ReadOnly);
        QString StyleSheet = QLatin1String(File.readAll());
        a.setStyleSheet(StyleSheet);
        QApplication::setQuitOnLastWindowClosed(false);


}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
