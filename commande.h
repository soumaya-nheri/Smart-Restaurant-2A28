#ifndef COMMANDE_H
#define COMMANDE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>
#include<QDate>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QSqlDatabase>
#include<QSqlRecord>
#include<QDebug>
class Commande
{
private :
    QString ID_COM;
    QString TYPE_COM;
    QDate DATE_COM;
    QString ID_STAFF;
    QString ID_CLIENT;
    QString ID_PLAT;
    QString ID_TABLE;
    QString i[2][5];

public:
    Commande();
    Commande(QString ID_COM,QString TYPE_COM,QDate DATE_COM,QString ID_STAFF,QString ID_CLIENT,QString ID_PLAT,QString id_table);
    ~Commande(){};

    void setId_com(QString ID_COM);
    void setType_com(QString TYPE_COM);
    void setDate_com(QDate DATE_COM);
    void setId_staff (QString ID_STAFF);
    void setId_client (QString ID_CLIENT);
    void setId_table(QString ID_PLAT);
    void setId_plat(QString id_plat);

    QString getId_com();
    QString getType_com();
    QDate getDate_com();
    QString getId_staff();
    QString getId_client();
    QString getId_table();
    QString getId_plat();

    bool Ajouter_commande();
    QSqlQueryModel * Afficher_commande();
    bool Modifier_commande();
    bool Supprimer_commande(QString ID_COM);
    QSqlQueryModel * trier_commandeDate();
    QSqlQueryModel * trier_commandeType();
    QSqlQueryModel * trier_commandeStaff();
    QSqlQueryModel * rechercher_commande(const QString &b);
    QSqlQueryModel * Stat_commande();
    QSqlQueryModel * Stat_commandeStaff();
    QSqlQueryModel * rechercher_com();
    QString afficher();
};

#endif // COMMANDE_H
