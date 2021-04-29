#include "commande.h"
Commande::Commande()
{
    ID_COM="";
    TYPE_COM="";
    ID_STAFF="";
    ID_CLIENT="";
    ID_PLAT="";
    ID_TABLE="";
}

Commande::Commande(QString ID_COM,QString TYPE_COM,QDate DATE_COM,QString ID_STAFF,QString ID_CLIENT,QString ID_PLAT,QString ID_TABLE)
{
    this->ID_COM=ID_COM;
    this->TYPE_COM=TYPE_COM;
    this->DATE_COM=DATE_COM;
    this->ID_STAFF=ID_STAFF;
    this->ID_CLIENT=ID_CLIENT;
    this->ID_PLAT=ID_PLAT;
    this->ID_TABLE=ID_TABLE;
}

void Commande::setId_com(QString ID_COM)
{
    this->ID_COM=ID_COM;
}

void Commande:: setType_com(QString TYPE_COM)
{
    this->TYPE_COM=TYPE_COM;
}

void Commande:: setDate_com(QDate DATE_COM)
{
    this->DATE_COM=DATE_COM;
}

void Commande:: setId_staff(QString ID_STAFF)
{
    this->ID_STAFF=ID_STAFF;
}

void Commande:: setId_client(QString ID_CLIENT)
{
    this->ID_CLIENT=ID_CLIENT;
}

void Commande:: setId_plat(QString ID_PLAT)
{
    this->ID_PLAT=ID_PLAT;
}

void Commande:: setId_table(QString ID_TABLE)
{
    this->ID_TABLE=ID_TABLE;
}


QString Commande:: getId_com()
{
    return ID_COM;
}

QString Commande:: getType_com()
{
    return TYPE_COM;
}

QDate Commande:: getDate_com()
{
    return DATE_COM;
}

QString Commande:: getId_staff()
{
    return ID_STAFF;
}

QString Commande:: getId_client()
{
    return ID_CLIENT;
}

QString Commande:: getId_plat()
{
    return ID_PLAT;
}

QString Commande:: getId_table()
{
    return ID_TABLE;
}


bool Commande:: Ajouter_commande()
{
    QSqlQuery query;
    query.prepare("INSERT INTO COMMANDES (ID_COM, TYPE_COM, DATE_COM, ID_STAFF, ID_CLIENT, ID_PLAT, ID_TABLE)" "VALUES (:ID_COM, :TYPE_COM, :DATE_COM, :ID_STAFF, :ID_CLIENT, :ID_PLAT, :ID_TABLE)");
    query.bindValue(":ID_COM",ID_COM);
    query.bindValue(":TYPE_COM",TYPE_COM);
    query.bindValue(":DATE_COM",DATE_COM);
    query.bindValue(":ID_STAFF",ID_STAFF);
    query.bindValue(":ID_CLIENT",ID_CLIENT);
    query.bindValue(":ID_PLAT",ID_PLAT);
    query.bindValue(":ID_TABLE",ID_TABLE);
    return query.exec();
}

QString Commande:: afficher()
{
    int i;
    QSqlQueryModel  model;
    QString name;
    model.setQuery("SELECT * FROM  PLATS P INNER JOIN COMMANDES C ON C.ID_PLAT=P.ID_PLAT");
    for(i=0; i<model.rowCount();i++)
   {
        name = model.record(i).value("NOM_PLAT").toString();
        qDebug() << name;
    }
    return name;

}

QSqlQueryModel * Commande:: Afficher_commande()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT ID_COM,TYPE_COM,DATE_COM,ID_STAFF,ID_CLIENT,ID_PLAT,ID_TABLE FROM COMMANDES");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_COM"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE_COM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATE_COM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ID_STAFF"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("ID_CLIENT"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ID_PLAT"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("ID_TABLE"));
    return model;
}
 QSqlQueryModel * Commande::rechercher_com()
 {
     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("SELECT TYPE_COM FROM COMMANDES");
     return model;
 }
bool Commande::Modifier_commande()
{
    QSqlQuery query;
    query.prepare("UPDATE COMMANDES SET TYPE_COM=:TYPE_COM, DATE_COM=:DATE_COM, ID_STAFF=:ID_STAFF, ID_CLIENT=:ID_CLIENT, ID_PLAT=:ID_PLAT, ID_TABLE=:ID_TABLE WHERE ID_COM=:ID_COM ");
    query.bindValue(":ID_COM",ID_COM);
    query.bindValue(":TYPE_COM",TYPE_COM);
    query.bindValue(":DATE_COM",DATE_COM);
    query.bindValue(":ID_STAFF",ID_STAFF);
    query.bindValue(":ID_CLIENT",ID_CLIENT);
    query.bindValue(":ID_PLAT",ID_PLAT);
    query.bindValue(":ID_TABLE",ID_TABLE);
    return query.exec();
}

bool Commande::Supprimer_commande(QString ID_COM)
{
    QSqlQuery query;
    query.prepare("DELETE FROM COMMANDES WHERE ID_COM=:ID_COM");
    query.bindValue(":ID_COM",ID_COM);
   return query.exec();
}

QSqlQueryModel * Commande::trier_commandeType()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM COMMANDES ORDER BY TYPE_COM");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_COM"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("TYPE_COM"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("DATE_COM"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_STAFF"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_CLIENT"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_PLAT"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_TABLE"));
    return model;
}

QSqlQueryModel * Commande::trier_commandeDate()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM COMMANDES ORDER BY DATE_COM");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_COM"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("TYPE_COM"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("DATE_COM"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_STAFF"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_CLIENT"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_PLAT"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_TABLE"));
    return model;
}

QSqlQueryModel * Commande::trier_commandeStaff()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM COMMANDES ORDER BY ID_STAFF");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_COM"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("TYPE_COM"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("DATE_COM"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_STAFF"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_CLIENT"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_PLAT"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_TABLE"));
    return model;
}

QSqlQueryModel * Commande::rechercher_commande(const QString &b)
{
   QSqlQueryModel * model = new QSqlQueryModel();
   model->setQuery("SELECT * FROM COMMANDES WHERE (ID_COM || TYPE_COM || DATE_COM || ID_STAFF || ID_CLIENT || ID_PLAT || ID_TABLE) LIKE '%"+b+"%'");
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_COM"));
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("TYPE_COM"));
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("DATE_COM"));
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_STAFF"));
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_CLIENT"));
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_PLAT"));
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_TABLE"));
   return model;
}

QSqlQueryModel * Commande:: Stat_commande()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT COUNT(*) FROM COMMANDES");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("nb commandes"));
    return model;
}

QSqlQueryModel * Commande::Stat_commandeStaff()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT ID_STAFF,COUNT(*) FROM COMMANDES GROUP BY ID_STAFF");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_staff"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nb commandes"));
    return model;
}
