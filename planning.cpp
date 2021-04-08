#include "planning.h"

planning::planning()
{

}

bool planning::ajouter()
{
    QSqlQuery query;



    query.prepare("INSERT INTO planning (date_presence, nb_heure,staff)"
                      "VALUES (:date_presence, :nb_heure,:staff)");

/*    query.bindValue(":id_presence",ID_PRESENCE);*/
    query.bindValue(":date_presence",DATE_PRESENCE);
    query.bindValue(":nb_heure",NB_HEURE);
    query.bindValue(":staff",STAFF);


    return query.exec();
}
QSqlQueryModel * planning::afficher()
{
    QSqlQueryModel *model= new QSqlQueryModel();

    model->setQuery("select staff,date_presence,nb_heure from planning order by date_presence");

    return model;
}

bool planning::supprimer(QString DATE_PRESENCE)
{
    QSqlQuery qry;
    qry.prepare("Delete from planning where date_presence = :date_presence");
    qry.bindValue(":date_presence",DATE_PRESENCE);
    return qry.exec();
}
