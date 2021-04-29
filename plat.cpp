#include "plat.h"

Plat::Plat()
{
    ID_PLAT="";
    NOM_PLAT="";
    DESCRIPTION_PLAT="";
    PRIX_PLAT="";
}

Plat::Plat(QString ID_PLAT,QString NOM_PLAT,QString DESCRIPTION_PLAT,QString PRIX_PLAT)
{
    this->ID_PLAT=ID_PLAT;
    this->NOM_PLAT=NOM_PLAT;
    this->DESCRIPTION_PLAT=DESCRIPTION_PLAT;
    this->PRIX_PLAT=PRIX_PLAT;
}

void Plat::setId_plat(QString ID_PLAT)
{
    this->ID_PLAT=ID_PLAT;
}

void Plat::setNom_plat(QString NOM_PLAT)
{
    this->NOM_PLAT=NOM_PLAT;
}

void Plat::setDescription_plat (QString DESCRIPTION_PLAT)
{
    this->DESCRIPTION_PLAT=DESCRIPTION_PLAT;
}

void Plat::setPrix_plat(QString PRIX_PLAT)
{
    this->PRIX_PLAT=PRIX_PLAT;
}

QString Plat::getId_plat()
{
    return ID_PLAT;
}

QString Plat::getNom_plat()
{
    return NOM_PLAT;
}

QString Plat::getDescription_plat()
{
    return DESCRIPTION_PLAT;
}

QString Plat::getPrix_plat()
{
    return PRIX_PLAT;
}


bool Plat::Ajouter_plat()
{
    QSqlQuery query;
    query.prepare("insert into PLATS (ID_PLAT,NOM_PLAT,DESCRIPTION_PLAT,PRIX_PLAT) " " values(:ID_PLAT,:NOM_PLAT,:DESCRIPTION_PLAT,:PRIX_PLAT)");
    query.bindValue(":ID_PLAT",ID_PLAT);
    query.bindValue(":NOM_PLAT",NOM_PLAT);
    query.bindValue(":DESCRIPTION_PLAT",DESCRIPTION_PLAT);
    query.bindValue(":PRIX_PLAT",PRIX_PLAT);
    return query.exec();
}

QSqlQueryModel * Plat::Afficher_plat()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM PLATS");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_PLAT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_PLAT"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTION_PLAT"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("PRIX_PLAT"));
    return model;
}

bool Plat::Modifier_plat()
{
    QSqlQuery query;
    query.prepare("UPDATE PLATS SET NOM_PLAT=:NOM_PLAT, DESCRIPTION_PLAT=:DESCRIPTION_PLAT, PRIX_PLAT=:PRIX_PLAT WHERE ID_PLAT=:ID_PLAT");
    query.bindValue(":ID_PLAT",ID_PLAT);
    query.bindValue(":NOM_PLAT",NOM_PLAT);
    query.bindValue(":DESCRIPTION_PLAT",DESCRIPTION_PLAT);
    query.bindValue(":PRIX_PLAT",PRIX_PLAT);
    return query.exec();
}

bool Plat::Supprimer_plat(QString ID_PLAT)
{
    QSqlQuery query;
    query.prepare("DELETE FROM PLATS WHERE ID_PLAT=:ID_PLAT");
    query.bindValue(":ID_PLAT",ID_PLAT);
   return query.exec();
}

QSqlQueryModel * Plat::trier_platNom()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM PLATS ORDER BY NOM_PLAT");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_PLAT"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NOM_PLAT"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("DESCRIPTION_PLAT"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("PRIX_PLAT"));
    return model;
}

QSqlQueryModel * Plat::trier_platDescription()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM PLATS ORDER BY DESCRIPTION_PLAT");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_PLAT"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NOM_PLAT"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("DESCRIPTION_PLAT"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("PRIX_PLAT"));
    return model;
}

QSqlQueryModel * Plat::trier_platPrix()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM PLATS ORDER BY PRIX_PLAT");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_PLAT"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NOM_PLAT"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("DESCRIPTION_PLAT"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("PRIX_PLAT"));
    return model;
}

QSqlQueryModel * Plat::rechercher_plat(const QString &b)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM PLATS WHERE (ID_PLAT || NOM_PLAT || DESCRIPTION_PLAT || PRIX_PLAT) LIKE '%"+b+"%'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_PLAT"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NOM_PLAT"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("DESCRIPTION_PLAT"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("PRIX_PLAT"));
    return model;
}

QSqlQueryModel * Plat::rechercher_plat2()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT NOM_PLAT FROM PLATS");
    return model;
}
