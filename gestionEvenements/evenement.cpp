#include "evenement.h"

Evenement::Evenement(int id, QString nom, double prix, QString date, QString description)
{
this->id = id;
    this->nom = nom;
    this->prix = prix;
    this->date = date;
    this->description = description;
}

Evenement::~Evenement()
{

}


int Evenement::get_id()
{
    return  id;
}
QString Evenement::get_nom()
{
    return  nom;
}
double Evenement::get_prix()
{
    return  prix;
}
QString Evenement::get_description()
{
    return  description;
}

QString Evenement::get_date()
{
    return  date;
}

void Evenement::set_id(int id)
{
    this->id = id;
}
void Evenement::set_nom(QString nom)
{
     this->nom = nom;

}
void Evenement::set_prix(double prix)
{
     this->prix = prix;
}
void Evenement::set_description(QString description)
{
     this->description = description;
}


void Evenement::set_date(QString date)
{
     this->date = date;
}
bool Evenement::add_evenement()
{
    QSqlQuery qry;
    qry.prepare(ADD_EVENEMENT_QUERY);
    qry.bindValue(":id",id);
    qry.bindValue(":nom",nom);
    qry.bindValue(":prix",prix);
    qry.bindValue(":date",date);
    qry.bindValue(":description",description);

    return qry.exec();
}
QSqlQueryModel * Evenement::show_evenements()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery(SELECT_ALL_PRODUCTS);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prix"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("date"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("description"));

    return model;

}

bool Evenement::delete_evenement(int id)
{
    QSqlQuery qry;
    qry.prepare(DELETE_PRODUCT_QUERY);
    qry.bindValue(":id",id);
    return qry.exec();
}

