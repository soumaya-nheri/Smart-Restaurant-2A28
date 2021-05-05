#include "produit.h"

Produit::Produit(QString id_p,QString type_p, QString desc_p,QString quantite_p,  QString prix_p)
{
    this-> id_p= id_p;
    this-> type_p= type_p;
    this-> desc_p=desc_p;
    this-> quantite_p= quantite_p;
   this->prix_p =prix_p;

}
bool Produit::ajouter()
{
    QSqlQuery query;

    query.prepare("insert into produit (id_p , type_p , desc_p ,quantite_p , prix_p)" "values (:id_p , :type_p , :desc_p ,:quantite_p , :prix_p)");

    query.bindValue(":id_p",id_p);
    query.bindValue(":type_p",type_p);
    query.bindValue(":desc_p",desc_p);
    query.bindValue(":quantite_p",quantite_p);
    query.bindValue(":prix_p",prix_p);


    return query.exec();

}

QSqlQueryModel * Produit::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from produit");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_p"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("type_p"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("desc_p"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("quantite_p"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("prix_p"));



    return model;


}

bool Produit::modifier(QString id_p,QString type_p, QString desc_p,QString quantite_p,  QString prix_p)
{
    QSqlQuery query;
    query.prepare("UPDATE produit SET id_p= :id_p,type_p= :type_p,desc_p= :desc_p,quantite_p= :quantite_p,prix_p= :prix_p Where id_p= :id_p");
    query.bindValue(":id_p",id_p);
    query.bindValue(":type_p",type_p);
    query.bindValue(":desc_p",desc_p);
    query.bindValue(":quantite_p",quantite_p);
    query.bindValue(":prix_p",prix_p);
    return query.exec();
}

bool Produit::supprimer(QString id_p)
{
    QSqlQuery query;
    query.prepare("Delete from produit where id_p= :id_p");
    query.bindValue(":id_p",id_p);
    return query.exec();
}
QSqlQueryModel * Produit::recherche(QString id_p)
{
QSqlQueryModel * model = new QSqlQueryModel();
QSqlQuery query;
query.prepare("select * from produit WHERE id_p = :id_p");
query.bindValue(":id_p",id_p);
query.exec();
model ->setQuery(query);
model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_p"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("type_p"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("desc_p"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("quantite_p"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("prix_p"));

return model;
}


int Produit ::stat(QString type)
{
    QSqlQuery query;
        int count=0 ;
        QSqlQuery requete("select from produit where type_p=:type  ") ;
        while(requete.next())

        {
                count++ ;
        }

    return(count);
}
int Produit ::nbtotal()
{
    QSqlQuery query;
        int count=0 ;
        QSqlQuery requete("select * from produit ") ;
        while(requete.next())

        {
                count++ ;
        }

    return(count);
}
QSqlQueryModel * Produit::statfinal(QString type_p)
{
    int s,n,f;
QSqlQueryModel * model = new QSqlQueryModel();
QSqlQuery query;
query.prepare("select * from produit WHERE type_p = :type_p");
query.bindValue(":type_p",type_p);
s=stat( type_p);
n=nbtotal();
f=(s*100)/n;
query.exec();
model ->setQuery(query);
model->setHeaderData(0,Qt::Horizontal,QObject::tr("statistique"));


return model;
}
