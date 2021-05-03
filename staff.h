#ifndef STAFF_H
#define STAFF_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
class staff
{
    QString cin,nom,prenom,email,telephone,login,password,role;

    int salaire;

public:

    staff();
    staff(QString c,QString n,QString p,QString e,QString t,QString l,QString pass,QString r,int s):cin(c),nom(n),prenom(p),email(e),telephone(t),login(l),password(pass),role(r),salaire(s){}
    bool ajouter();
    QSqlQueryModel *recherchestaff(QString);
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    QSqlQueryModel *rechercher(QString r);
};

#endif // STAFF_H
