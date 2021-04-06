#include "connection.h"
#include<QDebug>
#include<QMessageBox>

Connection::Connection(){}

bool Connection::createconnection()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("smart_restaurant");
    db.setUserName("behija");
    db.setPassword("behija");

    if (db.open())
    {
        test=true;
    }
    return test;
}

void Connection::closeconnection()
{
    QSqlDatabase db;
    db.close();
}






//SQLITE
/*void Connection::createTable()
{
   QSqlDatabase db;
   const QString createSQL ="CREATE TABLE COMMANDES" "(ID_COM NUMBER PRIMARY KEY," "TYPE_COM VARCHAR(20)," "DATE_COM VARCHAR(20)," "ID_STAFF NUMBER," "ID_CLIENT NUMBER," "ID_PLAT NUMBER," "ID_TABLE NUMBER);";
   QSqlQuery query(db);
   if(query.exec(createSQL))
   {
       QMessageBox::information(nullptr, QObject::tr("table is open"),
                   QObject::tr("tab successful.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
   }else
   {
       QMessageBox::critical(nullptr, QObject::tr("table is not open"),
                   QObject::tr("tab not successful.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
   }

}

void Connection::dropTable()
    {

         QSqlDatabase db;
        QSqlQuery query(db);

        const QString dropSQL = "DROP TABLE IF EXISTS COMMANDES";
        if(query.exec(dropSQL))
        {
            QMessageBox::information(nullptr, QObject::tr("table is drop"),
                        QObject::tr("tab drop successful.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }else
        {
            QMessageBox::critical(nullptr, QObject::tr("table is not drop"),
                        QObject::tr("tab not drop successful.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }

     }
*/
