#ifndef PRODUIT_H
#define PRODUIT_H
#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>


#include <QVariant>
#include <QComboBox>

class Produit
{
    QString id_p,type_p,desc_p,quantite_p,prix_p;

public:
    Produit(){};
    Produit(QString,QString,QString,QString,QString);

    QString getId(){return id_p;}
    QString getType_p(){return type_p;};
    QString getDesc_p(){return desc_p;}
    QString getQuantite_p(){return quantite_p;}
    QString getPrix_p(){return prix_p;}


    void setId (QString c ){id_p=c;}
    void setType_p(QString n){type_p=n;}
    void setDesc_p(QString p){desc_p=p;}
    void setQuantite_p(QString m){ quantite_p=m;}
    void setPrix_p(QString t){prix_p=t;}


    bool ajouter();
    QSqlQueryModel * afficher();
    bool modifier(QString,QString,QString,QString,QString);
    bool supprimer(QString);
    QSqlQueryModel * recherche(QString id_p);
    QSqlQueryModel * statfinal(QString type_p);
    int stat(QString type_p);
    int nbtotal();
};

#endif // CLIENT_H
