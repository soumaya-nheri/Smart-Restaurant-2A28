#ifndef DATABASE_H
#define DATABASE_H


#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>

class Database
{
public:
    Database();
    bool createconnect();
    void closeconnection();
protected:
    QSqlDatabase db;
};

#endif // DATABASE_H
