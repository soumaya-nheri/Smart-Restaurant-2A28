#include "tables.h"

Tables::Tables(QString Etat, QString Numero)
{
    this->Etat = Etat;
    this->Numero = Numero;

}

bool Tables::ajouter_2()
{
    QSqlQuery query;

    query.prepare("insert into tables (Etat,Numero)" "values (:Etat,:Numero)");

    query.bindValue(":Etat",Etat);
    query.bindValue(":Numero",Numero);


    return query.exec();

}

QSqlQueryModel * Tables::afficher_2()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from tables ORDER BY Numero");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Numero"));



    return model;


}

bool Tables::modifier_2(QString Etat, QString Numero)
{
    QSqlQuery query;
    query.prepare("UPDATE tables SET Etat= :Etat,Numero= :Numero Where Numero= Numero");
    query.bindValue(":Etat",Etat);
    query.bindValue(":Numero",Numero);

    return query.exec();
}

bool Tables::supprimer_2(QString Numero)
{
    QSqlQuery query;
    query.prepare("Delete from tables where Numero= :Numero");
    query.bindValue(":Numero",Numero);
    return query.exec();
}
QSqlQueryModel * Tables::cherchertable(QString Numero)
{
QSqlQueryModel * model = new QSqlQueryModel();
QSqlQuery query;
query.prepare("select * from tables WHERE Numero = :Numero");
query.bindValue(":Numero",Numero);
query.exec();
model ->setQuery(query);
model->setHeaderData(0,Qt::Horizontal,QObject::tr("Etat"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Numero"));

return model;
}

