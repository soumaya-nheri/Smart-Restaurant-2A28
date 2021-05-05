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
    QSqlQuery qry;//declaration d une requete sql
    QString prix_str=QString::number(prix);
    qry.prepare("INSERT INTO EVENEMENTS(id,nom,prix,da,description) VALUES (:id,:nom,:prix,:date,:description)");//preparation du requete
    qry.bindValue(":id",id);//affectation des valeurs a la requete : injection sql securité
    qry.bindValue(":nom",nom);
    qry.bindValue(":prix",prix_str);
    qry.bindValue(":date",date);
    qry.bindValue(":description",description);

    return qry.exec();
}
QSqlQueryModel * Evenement::show_evenements()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EVENEMENTS");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prix"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("date"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("description"));

    return model;

}

bool Evenement::delete_evenement(int id)
{ bool test=rechercher(id);
    QSqlQuery qry;
    qry.prepare("DELETE FROM EVENEMENTS WHERE id = :id");
    qry.bindValue(":id",id);
    qry.exec();
    return test;
}
bool Evenement::update_evenement(int id)
{   bool test=rechercher(id);
    QSqlQuery qry;
    qry.prepare("UPDATE EVENEMENTS set nom=:nom,prix=:prix,da=:date,description=:description where id=:id");
    qry.bindValue(":id",id);
    qry.bindValue(":nom",nom);
    qry.bindValue(":prix",prix);
    qry.bindValue(":date",date);
    qry.bindValue(":description",description);

     qry.exec();
     return test;
}
QSqlQueryModel * Evenement::tri_evenements(QString selon)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EVENEMENTS order by "+selon+"");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prix"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("date"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("description"));

    return model;

}
QSqlQueryModel * Evenement::find_evenements(QString selon,QString rech)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EVENEMENTS where "+selon+" like '"+rech+"%'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prix"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("date"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("description"));

    return model;

}
bool Evenement::rechercher(int id)
{
    QSqlQuery qry;
    qry.prepare("select * from evenements where id=:id");
    qry.bindValue(":id",id);
    qry.exec();
    return qry.next();
}
