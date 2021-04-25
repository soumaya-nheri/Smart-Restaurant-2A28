#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "produit.h"
#include "ajouterproduit.h"
#include "modifierproduit.h"
#include "supprimerproduit.h"
#include "fournisseur.h"
#include "ajouter_fournisseur.h"
#include "modifier_fournisseur.h"
#include "supprimer_fournisseur.h"
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include<QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>

Connection::Connection(){}

bool Connection::createconnection()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");//inserer le nom de la source de données ODBC
    db.setUserName("Khalil");//inserer nom de l'utilisateur
    db.setPassword("Khalil");//inserer mot de passe de cet utilisateur

    if (db.open())
    test=true;
    return  test;
}

void Connection::closeconnection(){db.close();}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_ajouterproduit_clicked()
{
    ajouterproduit ajouter;
    ajouter.setModal(true);
    ajouter.exec();

    Connection conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db);
    qry->prepare("select * from produit");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_produit->setModel(modal);

}

void MainWindow::on_pushButton_modifierproduit_clicked()
{
    modifierproduit modifier;
    modifier.setModal(true);
    modifier.exec();

    Connection conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db);
    qry->prepare("select * from produit");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_produit->setModel(modal);
}

void MainWindow::on_pushButton_supprimerproduit_clicked()
{
    supprimerproduit supp;
    supp.setModal(true);
    supp.exec();

    Connection conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db);
    qry->prepare("select * from produit");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_produit->setModel(modal);
}


void MainWindow::on_pushButton_chercherproduit_clicked()
{

            QString id_p= ui->lineEdit->text() ;
            ui->tableView_produit->setModel(tempproduit.recherche(id_p));


}



void MainWindow::on_pushButtonproduit_clicked()
{
      ui->tableView_produit->setModel(tempproduit.afficher());
}

void MainWindow::on_radioButton_pripr_clicked()
{
    Connection conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db);
    qry->prepare("select * from produit ORDER BY prix_p");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_produit->setModel(modal);
}

void MainWindow::on_radioButton_typepr_clicked()
{
    Connection conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db);
    qry->prepare("select * from produit ORDER BY type_p");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_produit->setModel(modal);
}

void MainWindow::on_radioButton_quantitepr_clicked()
{
    Connection conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db);
    qry->prepare("select * from produit ORDER BY quantite_p");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_produit->setModel(modal);
}


void MainWindow::on_pushButton_ajouter_fournisseur_clicked()
{
    ajouter_fournisseur ajouter;
    ajouter.setModal(true);
    ajouter.exec();

    Connection conn;
    QSqlQueryModel * modal1 = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db);
    qry->prepare("select * from fournisseur");
    qry->exec();
    modal1->setQuery(*qry);
    ui->tableView_fournisseur->setModel(modal1);
}

void MainWindow::on_pushButton_modifier_fournisseur_clicked()
{
    modifier_fournisseur modifier;
    modifier.setModal(true);
    modifier.exec();

    Connection conn;
    QSqlQueryModel * modal1 = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db);
    qry->prepare("select * from fournisseur");
    qry->exec();
    modal1->setQuery(*qry);
    ui->tableView_fournisseur->setModel(modal1);
}

void MainWindow::on_pushButton_supprimer_fournisseur_clicked()
{
    supprimer_fournisseur supp;
    supp.setModal(true);
    supp.exec();

    Connection conn;
    QSqlQueryModel * modal1 = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db);
    qry->prepare("select * from fournisseur");
    qry->exec();
    modal1->setQuery(*qry);
    ui->tableView_fournisseur->setModel(modal1);

}


void MainWindow::on_pushButton_afficherfournisseur_clicked()
{
    ui->tableView_fournisseur->setModel(tempfournisseur.afficher_2());

}

void MainWindow::on_pushButton_imprimerproduit_clicked()
{
    QPrinter printer;
     printer.setPrinterName("khalil");
     QPrintDialog dialog(&printer, this);
     if (dialog.exec() == QDialog::Rejected) return;
     ui->tableView_produit->render(&printer);
}







