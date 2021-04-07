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




