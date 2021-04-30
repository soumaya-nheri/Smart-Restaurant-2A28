#ifndef OFFRE_H
#define OFFRE_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include"querDefines.h"


class Offre
{
private:
int id;
QString nom;
double prix;
QString description ;

public:
    Offre(int id = 0, QString nom = "", double prix = 0.0 , QString description ="");
    ~Offre();
    // getteurs setteurs

    int get_id();
    QString get_nom();
    double get_prix();
    QString get_description() ;

    void set_id(int id);
    void set_nom(QString nom);
    void set_prix(double prix);
    void set_description(QString description) ;



    //
bool rechercher(int id);
    bool add_offre();
     bool update_offre(int);
    QSqlQueryModel * show_offres();
  //  bool modify_evenement();
    bool delete_offre(int id);

};




#endif // OFFRE_H
