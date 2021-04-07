#ifndef CONNEXION_H
#define CONNEXION_H


#include <QSqlDatabase>
#include <QtSql>

class Connection
{
    QSqlDatabase db;
public:
    Connection();
    ~Connection();
    bool CreateConnection();
    void CloseConnection() ;
};


#endif // CONNEXION_H
