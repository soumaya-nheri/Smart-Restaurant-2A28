#ifndef EVENEMENT_H
#define EVENEMENT_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include"querDefines.h"



class Evenement
{
    private:
    int id;
    QString nom;
    double prix;
    QString date;
    QString description ;

public:
    Evenement(int id = 0, QString nom = "", double prix = 0.0, QString date = "", QString description ="");
    ~Evenement();
    // getteurs setteurs
    int get_id();
    QString get_nom();
    double get_prix();
    QString get_description() ;
    QString get_date() ;

    void set_id(int id);
    void set_nom(QString nom);
    void set_prix(double prix);
    void set_description(QString description) ;
    void set_date(QString date) ;

    bool rechercher(int id);
    bool update_evenement(int);
    bool add_evenement();
    QSqlQueryModel * show_evenements();
    QSqlQueryModel * tri_evenements(QString);
      QSqlQueryModel * find_evenements(QString,QString);
    bool delete_evenement(int id);


};

#endif // EVENEMENT_H
