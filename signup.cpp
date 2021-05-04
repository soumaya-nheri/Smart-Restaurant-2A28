#include "signup.h"

signup::signup()
{
    usern="";
    mdp="";

}

signup::signup(QString usern,QString mdp)
{
    this->usern=usern;
    this->mdp=mdp;


}

QString signup::GetUsername(){return usern;}
QString signup::Getmdp(){return mdp;}



bool signup::ajouter()
{
QSqlQuery query;
 query.prepare("INSERT INTO CONNEXIONU (USERN,MDP)"
        "VALUES(:usern, :mdp)");
 query.bindValue(":usern",usern);
 query.bindValue(":mdp",mdp);

return query.exec();
}
