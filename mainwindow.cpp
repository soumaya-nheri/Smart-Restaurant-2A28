#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commande.h"
#include "plat.h"
#include <QApplication>
#include <QMessageBox>
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QWidget>
#include<QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>
#include<QPropertyAnimation>
#include<QSound>
#include<QMediaPlayer>
#include<QPushButton>
#include<QTabWidget>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*animation = new QPropertyAnimation(ui->pushButton_ajoutercom, "geomertry");
    animation->setDuration(1000);
    animation->setStartValue(ui->pushButton_ajoutercom->geometry());
    animation->setEndValue(QRect(200,200,100,50));
    animation->start();*/
    click = new QMediaPlayer();
    click->setMedia(QUrl::fromLocalFile("C:/Users/Behija/Documents/CRUD1/Click.wav"));

    //click = new QMediaPlayer();
    //click->setMedia(QUrl::fromLocalFile("C:\Users\Behija\Documents\CRUD1\sound/Click.wav"));
    ui->tableView_afficherCom->setModel(Com.Afficher_commande());
    ui->tableView_statCom->setModel(Com.Stat_commande());
    ui->tableView_afficherPlat->setModel(P.Afficher_plat());

}

MainWindow::~MainWindow()
{
    delete ui;
}

//Commandes
void MainWindow::on_pushButton_ajoutercom_clicked()
{
    //QSound::play("Click.wav");
    //QSound  bells("Click.wav");
    //bells.play();

    //click->setMedia(QUrl::fromLocalFile("C:/Users/Behija/Documents/CRUD1/Click.mp3"));
    click->play();
//sound
    //click = new QMediaPlayer();
    //click->setMedia(QUrl::fromLocalFile("C:/Users/HP/Desktop/2A12/project c++/qt/E-Clinic/Click.mp3"));
    QString ID_COM=ui->lineEdit_idcom->text();
    QString TYPE_COM=ui->lineEdit_typecom->text();
    QDate DATE_COM=ui->dateEdit_com->date();
    QString ID_STAFF=ui->lineEdit_idstaffB->text();
    QString ID_CLIENT=ui->lineEdit_idclientB->text();
    QString ID_PLAT=ui->lineEdit_idplatB->text();
    QString ID_TABLE=ui->lineEdit_idtableB->text();
    Commande C(ID_COM,TYPE_COM,DATE_COM,ID_STAFF,ID_CLIENT,ID_PLAT,ID_TABLE);
    bool test=C.Ajouter_commande();
    if(test)
    {
        ui->tableView_afficherCom->setModel(Com.Afficher_commande());
        ui->tableView_statCom->setModel(Com.Stat_commande());

        QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("Ajout effectué.\n click cancel to exit."),QMessageBox::Cancel);
        ui->tabWidget_commande->setCurrentWidget(ui->afficherCom);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not ok"),QObject::tr("Ajout non effectué.\n click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_modifierCom_clicked()
{
    int row=ui->tableView_afficherCom->selectionModel()->currentIndex().row();
    QString ID_COM=ui->tableView_afficherCom->model()->index(row,0).data().toString();
    QString TYPE_COM=ui->tableView_afficherCom->model()->index(row,1).data().toString();
    QDate DATE_COM=ui->tableView_afficherCom->model()->index(row,2).data().toDate();
    QString ID_STAFF=ui->tableView_afficherCom->model()->index(row,3).data().toString();
    QString ID_CLIENT=ui->tableView_afficherCom->model()->index(row,4).data().toString();
    QString ID_PLAT=ui->tableView_afficherCom->model()->index(row,5).data().toString();
    QString ID_TABLE=ui->tableView_afficherCom->model()->index(row,6).data().toString();
    if(row==-1)
    {
        QMessageBox ::critical(nullptr,QObject::tr("modifier un service"),
                                          QObject::tr("aucune selection.\n"
                                              "click ok to exit"),QMessageBox::Ok);
    }
    else
    {

        ui->lineEdit_idcom_2->setText(ID_COM);
        ui->lineEdit_typecom_2->setText(TYPE_COM);
        ui->dateEdit_com_2->setDate(DATE_COM);
        ui->lineEdit_idstaffB_2->setText(ID_STAFF);
        ui->lineEdit_idclientB_2->setText(ID_CLIENT);
        ui->lineEdit_idplatB_2->setText(ID_PLAT);
        ui->lineEdit_idtableB_2->setText(ID_TABLE);
    }
}

void MainWindow::on_pushButton_vaModificationCom_clicked()
{
    QString ID_COM=ui->lineEdit_idcom_2->text();
    QString TYPE_COM=ui->lineEdit_typecom_2->text();
    QDate DATE_COM=ui->dateEdit_com_2->date();
    QString ID_STAFF=ui->lineEdit_idstaffB_2->text();
    QString ID_CLIENT=ui->lineEdit_idclientB_2->text();
    QString ID_PLAT=ui->lineEdit_idplatB_2->text();
    QString ID_TABLE=ui->lineEdit_idtableB_2->text();
    Commande C(ID_COM,TYPE_COM,DATE_COM,ID_STAFF,ID_CLIENT,ID_PLAT,ID_TABLE);
    bool test=C.Modifier_commande();
    if(test)
    {
        ui->tableView_afficherCom->setModel(Com.Afficher_commande());
        QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("Ajout effectué.\n click cancel to exit."),QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not ok"),QObject::tr("Ajout non effectué.\n click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_supprimercom_clicked()
{
    QPushButton button("Oops! vous venez de perdre une commande!");
        button.show();
    QString ID_COM=ui->lineEdit_idcomSup->text();
    bool test=Com.Supprimer_commande(ID_COM);
    if(test)
    {
         ui->tableView_afficherCom->setModel(Com.Afficher_commande());
         ui->tableView_statCom->setModel(Com.Stat_commande());
        QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("Ajout effectué.\n click cancel to exit."),QMessageBox::Cancel);

    }
    else
       QMessageBox::critical(nullptr, QObject::tr("Not ok"),QObject::tr("Ajout non effectué.\n click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_rechercherCom_clicked()
{
    if(ui->lineEdit_rechercherCom->text() == "")
        {
            ui->tableView_afficherCom->setModel(Com.Afficher_commande());
        }
    else
        {
             ui->tableView_afficherCom->setModel(Com.rechercher_commande(ui->lineEdit_rechercherCom->text()));
        }

}

void MainWindow::on_pushButton_imprimerCom_clicked()
{
    QPrinter printer;
     printer.setPrinterName("bahouja");
     QPrintDialog dialog(&printer, this);
     if (dialog.exec() == QDialog::Rejected) return;
     ui->afficherCom->render(&printer);

}

void MainWindow::on_radioButton_triedateCom_clicked()
{
    ui->tableView_afficherCom->setModel(Com.trier_commandeDate());
}

void MainWindow::on_radioButton_trietypeCom_clicked()
{
    ui->tableView_afficherCom->setModel(Com.trier_commandeType());
}

void MainWindow::on_radioButton_trieidstaff_clicked()
{
    ui->tableView_afficherCom->setModel(Com.trier_commandeStaff());
}

//Plats
void MainWindow::on_pushButton_ajouterplat_clicked()
{
    QString ID_PLAT=ui->lineEdit_idPlat->text();
    QString NOM_PLAT=ui->lineEdit_nomplat->text();
    QString DESCRIPTION_PLAT=ui->lineEdit_descriptionplat->text();
    QString PRIX_PLAT=ui->lineEdit_prixplat->text();

    Plat P(ID_PLAT,NOM_PLAT,DESCRIPTION_PLAT,PRIX_PLAT);
    bool test=P.Ajouter_plat();
    if(test)
    {
        ui->tableView_afficherPlat->setModel(P.Afficher_plat());
        QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("Ajout effectué.\n click cancel to exit."),QMessageBox::Cancel);
        ui->tabWidget_Plat->setCurrentWidget(ui->afficherPlat);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not ok"),QObject::tr("Ajout non effectué.\n click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_modifierPlat_clicked()
{
    int row=ui->tableView_afficherPlat->selectionModel()->currentIndex().row();
    QString ID_PLAT=ui->tableView_afficherPlat->model()->index(row,0).data().toString();
    QString NOM_PLAT=ui->tableView_afficherPlat->model()->index(row,1).data().toString();
    QString DESCRIPTION_PLAT=ui->tableView_afficherPlat->model()->index(row,2).data().toString();
    QString PRIX_PLAT=ui->tableView_afficherPlat->model()->index(row,3).data().toString();

    if(row==-1)
    {
        QMessageBox ::critical(nullptr,QObject::tr("modifier un service"),
                                          QObject::tr("aucune selection.\n"
                                              "click ok to exit"),QMessageBox::Ok);
    }
    else
    {
        ui->lineEdit_idPlat_2->setText(ID_PLAT);
        ui->lineEdit_nomplat_2->setText(NOM_PLAT);
        ui->lineEdit_descriptionplat_2->setText(DESCRIPTION_PLAT);
        ui->lineEdit_prixplat_2->setText(PRIX_PLAT);

    }

}

void MainWindow::on_pushButton_vaModificationPlat_clicked()
{
    QString ID_PLAT=ui->lineEdit_idPlat_2->text();
    QString NOM_PLAT=ui->lineEdit_nomplat_2->text();
    QString DESCRIPTION_PLAT=ui->lineEdit_descriptionplat_2->text();
    QString PRIX_PLAT=ui->lineEdit_prixplat_2->text();
    Plat P(ID_PLAT,NOM_PLAT,DESCRIPTION_PLAT,PRIX_PLAT);
    bool test=P.Modifier_plat();
    if(test)
    {
        ui->tableView_afficherPlat->setModel(P.Afficher_plat());
        QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("Ajout effectué.\n click cancel to exit."),QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not ok"),QObject::tr("Ajout non effectué.\n click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_supprimerplat_clicked()
{
    QString ID_PLAT=ui->lineEdit_idplatSup->text();
    bool test=P.Supprimer_plat(ID_PLAT);
    if(test)
    {
         ui->tableView_afficherPlat->setModel(P.Afficher_plat());
        QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("Ajout effectué.\n click cancel to exit."),QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not ok"),QObject::tr("Ajout non effectué.\n click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_imprimerPlat_clicked()
{
    QPrinter printer;
     printer.setPrinterName("bahouja");
     QPrintDialog dialog(&printer, this);
     if (dialog.exec() == QDialog::Rejected) return;
     ui->tableView_afficherPlat->render(&printer);
}

void MainWindow::on_radioButton_trienomPlat_clicked()
{
    ui->tableView_afficherPlat->setModel(P.trier_platNom());
}

void MainWindow::on_radioButton_TriedesPlat_clicked()
{
    ui->tableView_afficherPlat->setModel(P.trier_platDescription());
}

void MainWindow::on_radioButton_trieprixPlat_clicked()
{
    ui->tableView_afficherPlat->setModel(P.trier_platPrix());
}

void MainWindow::on_pushButton_rechercherPlat_clicked()
{
    if(ui->lineEdit_rechercherPlat->text() == "")
        {
            ui->tableView_afficherPlat->setModel(P.Afficher_plat());
        }
    else
        {
             ui->tableView_afficherPlat->setModel(P.rechercher_plat(ui->lineEdit_rechercherPlat->text()));
        }

}


