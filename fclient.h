#ifndef FCLIENT_H
#define FCLIENT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>


class fclient
{
public:
    fclient();
   fclient(QString,QString,QString,QString,QString,QString);
    QString get_id();
     QString get_nom();
    QString get_prenom();
    QString get_num();
    QString get_mail();
    QString get_adress();
    void Refresh();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
private:
    QString id,nom,prenom,num,mail,adress;
};

#endif // FCLIENT_H


