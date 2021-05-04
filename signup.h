#ifndef SIGNUP_H
#define SIGNUP_H
#include "QString"
#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
class signup
{

    QString usern, mdp;

public:

    signup();
    signup(QString,QString);

    QString GetUsername();
    QString Getmdp();
    QString GetName();
    QString GetPoste();

    void SetUsername(QString U){usern=U;}
    void SetPassword(QString P){mdp=P;}


        bool ajouter();

};

#endif // SIGNUP_H
