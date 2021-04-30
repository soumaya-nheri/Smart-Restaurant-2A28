#ifndef QUERDEFINES_H
#define QUERDEFINES_H
//  les requetes SQL(CRUD )du module EVENEMENTS
#define ADD_EVENEMENT_QUERY  "INSERT INTO EVENEMENTS(id,nom,prix,date,description) VALUES (:id,:nom,:prix,:date,:description)"
#define SELECT_ALL_PRODUCTS  "SELECT * FROM EVENEMENTS "
#define DELETE_PRODUCT_QUERY  "DELETE FROM EVENEMENTS WHERE id = :id "

//  les requetes SQL(CRUD) du module OFFRES

#define ADD_OFFRE_QUERY  "INSERT INTO OFFRES(id,nom,prix,description) VALUES (:id,:nom,:prix,:description)"
#define SELECT_ALL_OFFRES  "SELECT * FROM OFFRES "
#define DELETE_OFFRE_QUERY  "DELETE FROM OFFRES WHERE id = :id "
#endif // QUERDEFINES_H
