#include "flivraison.h"
#include <QDebug>

flivraison::flivraison()
{
id="";
date="";
lieu="";
etat="";

}

flivraison::flivraison(QString id,QString date,QString lieu,QString etat)
{
    this->id=id;
    this->date=date;
    this->lieu=lieu;
    this->etat=etat;

}
QString flivraison::get_id(){return id;}
QString flivraison::get_date(){return date;}
QString flivraison::get_lieu(){return lieu;}
QString flivraison::get_etat(){return etat;}







bool flivraison::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO  livraison(ID,DATEE,LIEU,ETAT) VALUES (:id,:date,:lieu,:etat)");
     query.bindValue(":id",id);
    query.bindValue(":date",date);
     query.bindValue(":lieu",lieu);
    query.bindValue(":etat",etat);


    return query.exec();

  }


bool flivraison::supprimer(QString idd)
{
QSqlQuery query;

    query.prepare("Delete from livraison where ID = :id");
    query.bindValue(":id",idd);
return    query.exec();


}
 QSqlQueryModel * flivraison::afficher()
 {
     QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * from livraison");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("LIEU"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("ETAT"));


     return model;
 }
