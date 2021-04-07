#include "offre.h"
Offre::Offre(int id, QString nom, double prix ,QString description)
{
    this->id = id;
    this->nom = nom;
    this->prix = prix;
    this->description = description;
}


Offre::~Offre()
{

}


int Offre::get_id()
{
    return  id;
}
QString Offre::get_nom()
{
    return  nom;
}
double Offre::get_prix()
{
    return  prix;
}
QString Offre::get_description()
{
    return  description;
}

void Offre::set_id(int id)
{
    this->id = id;
}
void Offre::set_nom(QString nom)
{
     this->nom = nom;

}
void Offre::set_prix(double prix)
{
     this->prix = prix;
}
void Offre::set_description(QString description)
{
     this->description = description;
}

bool Offre::add_offre()
{
    QSqlQuery qry;
    qry.prepare(ADD_OFFRE_QUERY);
    qry.bindValue(":id",id);
    qry.bindValue(":nom",nom);
    qry.bindValue(":prix",prix);
    qry.bindValue(":description",description);

    return qry.exec();
}
QSqlQueryModel * Offre::show_offres()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery(SELECT_ALL_OFFRES);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prix"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("description"));

    return model;

}

bool Offre::delete_offre(int id)
{
    QSqlQuery qry;
    qry.prepare(DELETE_OFFRE_QUERY);
    qry.bindValue(":id",id);
    return qry.exec();
}


