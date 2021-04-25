#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase myb = QSqlDatabase::addDatabase("QODBC");
mydb.setDatabaseName("projet2_A");//inserer le nom de la source de données ODBC
mydb.setUserName("system");//inserer nom de l'utilisateur
mydb.setPassword("12345678");//inserer mot de passe de cet utilisateur

if (mydb.open())
test=true;





    return  test;
}
