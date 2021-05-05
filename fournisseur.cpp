#include "fournisseur.h"

Fournisseur::Fournisseur(QString id_f, QString nom_f,QString type_f ,QString num_f)
{
    this->id_f=id_f;
    this->nom_f=nom_f;
    this->type_f=type_f;
    this->num_f=num_f;

}

bool Fournisseur::ajouter_2()
{
    QSqlQuery query;

    query.prepare("insert into fournisseur (id_f,nom_f,type_f,num_f)" "values (:id_f,:nom_f,:type_f,:num_f)");

    query.bindValue(":id_f",id_f);
    query.bindValue(":nom_f",nom_f);
     query.bindValue(":type_f",type_f);
      query.bindValue(":num_f",num_f);


    return query.exec();

}

QSqlQueryModel * Fournisseur::afficher_2()
{
    QSqlQueryModel * model1=new QSqlQueryModel();

    model1->setQuery("select * from fournisseur");
    model1->setHeaderData(0,Qt::Horizontal,QObject::tr("id_f"));
    model1->setHeaderData(1,Qt::Horizontal,QObject::tr("nom_f"));
    model1->setHeaderData(2,Qt::Horizontal,QObject::tr("type_f"));
     model1->setHeaderData(3,Qt::Horizontal,QObject::tr("num_f"));

    return model1;


}

bool Fournisseur::modifier_2(QString id_f, QString nom_f,QString type_f ,QString num_f)
{
    QSqlQuery query;
    query.prepare("UPDATE fournisseur SET id_f=:id_f,nom_f=:nom_f,type_f=:type_f,num_f=:num_f Where id_f=:id_f");
    query.bindValue(":id_f",id_f);
    query.bindValue(":nom_f",nom_f);
    query.bindValue(":type_f",type_f);
     query.bindValue(":num_f",num_f);
    return query.exec();
}

bool Fournisseur::supprimer_2(QString id_f)
{
    QSqlQuery query;
    query.prepare("delete from fournisseur where id_f= :id_f");
    query.bindValue(":id_f",id_f);
    return query.exec();
}

