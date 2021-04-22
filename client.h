#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include<qdatetimeedit.h>
#include<qdatetime.h>
#include <QVariant>
#include <QComboBox>

class Client
{
    QString CIN,Nom,Prenom,Mail,Tel;
    QDate Dat;
public:
    Client(){};
    Client(QString,QString,QString,QString,QString,QDate);

    QString getCIN(){return CIN;}
    QString getNom(){return Nom;};
    QString getPrenom(){return Prenom;}
    QString getMail(){return Mail;}
    QString getTel(){return Tel;}
    QDate getDate(){return Dat;}

    void setCIN (QString c ){CIN=c;}
    void setNom(QString n){Nom=n;}
    void setPrenom(QString p){Prenom=p;}
    void setMail(QString m){ Mail=m;}
    void setTel(QString t){Tel=t;}
    void setDate(QDate d){Dat=d;}

    bool ajouterres();
    QSqlQueryModel * afficherres();
    bool modifierres(QString,QString,QString,QString,QString,QDate);
    bool supprimerres(QString);
    QSqlQueryModel * cherchercinres(QString CIN);
};

#endif // CLIENT_H
