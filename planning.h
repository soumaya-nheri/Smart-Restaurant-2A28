#ifndef planning_H
#define planning_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <QDate>
class planning
{
    QString ID_PRESENCE;
    QDate DATE_PRESENCE;
    int NB_HEURE;
    QString STAFF;

public:

    planning();
    planning(QString i, QDate d,int n, QString s):ID_PRESENCE(i),DATE_PRESENCE(d),NB_HEURE(n),STAFF(s){}
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
};

#endif // planning_H
