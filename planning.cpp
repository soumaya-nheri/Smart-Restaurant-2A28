#include "planning.h"
/*
planning::planning()
{

}

bool planning::ajouter()
{
    QSqlQuery query;



    query.prepare("INSERT INTO planning (cin, nom, prenom,email,telephone,login,password,role,salaire)"
                      "VALUES (:cin, :nom, :prenom,:email,:telephone,:login,:password,:role,:salaire)");

    query.bindValue(":cin",cin);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":email",email);
    query.bindValue(":telephone",telephone);
    query.bindValue(":login",login);
    query.bindValue(":password",password);
    query.bindValue(":role",role);
    query.bindValue(":salaire",salaire);

    return query.exec();
}
QSqlQueryModel * planning::afficher()
{
    QSqlQueryModel *model= new QSqlQueryModel();

    model->setQuery("select * from planning");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Telephone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Login"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Mot de passe"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Rôle"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Salaire"));


    return model;
}

bool planning::supprimer(QString cin)
{
    QSqlQuery qry;
    qry.prepare("Delete from planning where CIN = :CIN");
    qry.bindValue(":CIN",cin);
    return qry.exec();
}
*/
