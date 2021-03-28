#include "database.h"

Database::Database()
{

}
bool Database::createconnect()
{bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("Wassim");
    db.setPassword("esprit18");

    if (db.open()){
        test=true; qDebug() << "database opened";}
    return  test;
}
void Database::closeconnection(){
    db.close();
    qDebug() << "database closed";
    db.removeDatabase(QSqlDatabase::defaultConnection);
}
