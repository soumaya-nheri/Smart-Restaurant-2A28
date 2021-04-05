#include "fclient.h"
#include <QDebug>

fclient::fclient()
{
id="";
nom="";
prenom="";
num="";
adress="";
mail="";
}

fclient::fclient(QString id,QString nom,QString prenom,QString num,QString mail,QString adress)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->num=num;
    this->mail=mail;
    this->adress=adress;
}
QString fclient::get_id(){return id;}
QString fclient::get_nom(){return nom;}
QString fclient::get_prenom(){return prenom;}
QString fclient::get_num(){return num;}
QString fclient::get_mail(){return mail;}
QString fclient::get_adress(){return adress;}






bool fclient::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO  CLIENT(ID,NOM,PRENOM,NUM,MAIL,ADRESS) VALUES (:id,:nom,:prenom,:num,:mail,:adress)");
     query.bindValue(":id",id);
    query.bindValue(":nom",nom);
     query.bindValue(":prenom",prenom);
    query.bindValue(":num",num);
    query.bindValue(":mail",mail);
    query.bindValue(":adress",adress);

    return query.exec();

  }


bool fclient::supprimer(QString idd)
{
QSqlQuery query;

    query.prepare("Delete from CLIENT where ID = :id");
    query.bindValue(":id",idd);
return    query.exec();


}
 QSqlQueryModel * fclient::afficher()
 {
     QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * from CLIENT");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUM"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("MAIL"));
 model->setHeaderData(5, Qt::Horizontal, QObject::tr("ADRESS"));

     return model;
 }


