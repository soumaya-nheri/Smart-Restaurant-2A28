#include "connection.h"


Connection::Connection(){}

bool Connection::createconnection()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("Wassim");
    db.setPassword("esprit18");

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




