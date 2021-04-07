#ifndef TABLES_H
#define TABLES_H
#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>

class Tables
{
    QString Etat,Numero;

public:
    Tables(){};
    Tables(QString,QString);
    QString getEtat(){return Etat;}
    QString getNumero(){return Numero;};


    void setEtat (QString e ){Etat=e;}
    void setNumero(QString n){Numero=n;}

    bool ajouter_2();
    QSqlQueryModel * afficher_2();
    bool modifier_2(QString,QString);
    bool supprimer_2(QString);
    QSqlQueryModel * cherchertable(QString Numero);

};

#endif // TABLES_H
