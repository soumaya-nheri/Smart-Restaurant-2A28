#ifndef FLIVRAISON_H
#define FLIVRAISON_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>


class flivraison
{
public:
    flivraison();
   flivraison(QString,QString,QString,QString);
    QString get_id();
     QString get_date();
    QString get_lieu();
    QString get_etat();

    void Refresh();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
private:
    QString id,date,lieu,etat;
};

#endif // Flivraison_H
