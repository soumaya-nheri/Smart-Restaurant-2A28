#include "mainwindow.h"
#include "mainwindow0.h"
#include <QApplication>
#include <QFile>
#include <QTranslator>
#include <QInputDialog>
#include "mainwindow0.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Database db;
    db.createconnect();
    MainWindow0 w;

    /*
    //debut config langue
    QTranslator T;
    QStringList langue;
    langue<<"English"<<"Francais";
    const QString languel=QInputDialog::getItem(NULL,"Langue","Selectionner langue",langue);
    if(languel=="English")
        T.load(":/english.qm");
    if(languel!="Francais")
        a.installTranslator(&T);
    //fin config langue*/


    QFile file(":/new/prefix1/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet { QLatin1String(file.readAll()) };
    a.setStyleSheet(styleSheet);

    Connection1 c;
     bool test=c.createconnection1();
     if(test)
     {w.show();
         QMessageBox::information(nullptr, QObject::tr("database is open"),
                     QObject::tr("connection successful.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

         QApplication::setQuitOnLastWindowClosed(false);


 }
     else
         QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                     QObject::tr("connection failed.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);


    return a.exec();
}
