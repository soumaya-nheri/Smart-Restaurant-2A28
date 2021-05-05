#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>

class Fournisseur
{
    QString id_f,nom_f,type_f,num_f;

public:
    Fournisseur(){};
    Fournisseur(QString,QString,QString,QString);
    QString getId_f(){return id_f;}
    QString getNom_f(){return nom_f;};
    QString getType_f(){return type_f;};
    QString getNum_f(){return num_f;};


    void setId_f (QString e ){id_f=e;}
    void setNom_f(QString n){nom_f=n;}
    void setType_f(QString t){type_f=t;}
    void setNum_f(QString x){num_f=x;}

    bool ajouter_2();
    QSqlQueryModel * afficher_2();
    bool modifier_2(QString,QString,QString,QString);
    bool supprimer_2(QString);
};

#endif // FOURNISSEUR_H
