#ifndef PLAT_H
#define PLAT_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
class Plat
{
private :
    QString ID_PLAT;
    QString NOM_PLAT;
    QString DESCRIPTION_PLAT;
    QString PRIX_PLAT;

public:
    Plat();
    Plat(QString ID_PLAT,QString NOM_PLAT,QString DESCRIPTION_PLAT,QString PRIX_PLAT);
    ~Plat(){};

    void setId_plat(QString ID_PLAT);
    void setNom_plat(QString NOM_PLAT);
    void setDescription_plat (QString DESCRIPTION_PLAT);
    void setPrix_plat(QString PRIX_PLAT);

    QString getId_plat();
    QString getNom_plat();
    QString getDescription_plat();
    QString getPrix_plat();

    bool Ajouter_plat();
    QSqlQueryModel * Afficher_plat();
    bool Modifier_plat();
    bool Supprimer_plat(QString ID_PLAT);
    QSqlQueryModel * trier_platNom();
    QSqlQueryModel * trier_platDescription();
    QSqlQueryModel * trier_platPrix();
    QSqlQueryModel * rechercher_plat(const QString &b);
    QSqlQueryModel * rechercher_plat2();
};

#endif // PLAT_H
