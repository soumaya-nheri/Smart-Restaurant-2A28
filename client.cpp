#include "client.h"

Client::Client(QString CIN,QString Nom, QString Prenom,QString Mail,  QString Tel, QDate Dat)
{
    this->CIN = CIN;
    this->Nom = Nom;
    this->Prenom = Prenom;
    this->Mail = Mail;
   this->Tel = Tel;
   this->Dat=Dat;
}
bool Client::ajouterres()
{
    QSqlQuery query;

    query.prepare("insert into reservation (CIN, Nom, Prenom, Mail,  Tel,Dat)" "values (:CIN, :Nom, :Prenom, :Mail, :Tel, :Dat)");

    query.bindValue(":CIN",CIN);
    query.bindValue(":Nom",Nom);
    query.bindValue(":Prenom",Prenom);
    query.bindValue(":Mail",Mail);
    query.bindValue(":Tel",Tel);
    query.bindValue(":Dat",Dat);

    return query.exec();

}

QSqlQueryModel * Client::afficherres()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from reservation");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Mail"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Tel"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date"));


    return model;


}

bool Client::modifierres(QString CIN, QString Nom, QString Prenom, QString Mail, QString Tel, QDate Dat)
{
    QSqlQuery query;
    query.prepare("UPDATE reservation SET CIN= :CIN,Nom= :Nom,Prenom= :Prenom,Mail= :Mail,Tel= :Tel,Dat= :Dat Where CIN= :CIN");
    query.bindValue(":CIN",CIN);
    query.bindValue(":Nom",Nom);
    query.bindValue(":Prenom",Prenom);
    query.bindValue(":Mail",Mail);
    query.bindValue(":Tel",Tel);
    query.bindValue(":Dat",Dat);
    return query.exec();
}

bool Client::supprimerres(QString CIN)
{
    QSqlQuery query;
    query.prepare("Delete from reservation where CIN= :CIN");
    query.bindValue(":CIN",CIN);
    return query.exec();
}
QSqlQueryModel * Client::cherchercinres(QString CIN)
{
QSqlQueryModel * model = new QSqlQueryModel();
QSqlQuery query;
query.prepare("select * from reservation WHERE CIN = :CIN");
query.bindValue(":CIN",CIN);
query.exec();
model ->setQuery(query);
model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Mail"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("Tel"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date"));

return model;
}
