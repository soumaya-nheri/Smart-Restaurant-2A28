#include "connexion.h"


Connection::Connection()
{

}


Connection::~Connection()
{

}


bool Connection::CreateConnection()
{
    bool test=false;
    db = QSqlDatabase::addDatabase("QODBC");
        db.setDatabaseName("projet");
        db.setUserName("bacim");
        db.setPassword("bacim");
       if(db.open())
       {
           qDebug()<<"Database opened!";
       test=true;
       }
    else
       {
           qDebug() << db.lastError().text();
       }
       return test;
}


void Connection::CloseConnection()
{
    db.close();
}

