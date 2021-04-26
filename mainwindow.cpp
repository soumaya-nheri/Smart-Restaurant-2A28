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
#include<QMediaPlayer>
#include<QTabWidget>
#include<QCompleter>
#include<QFileSystemModel>
#include<QSqlRecord>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//music
    click = new QMediaPlayer();
    click->setMedia(QUrl::fromLocalFile("C:/Users/Behija/Desktop/Smart-Restaurant-2A28/Click.wav"));
    music = new QMediaPlayer();
    music->setMedia(QUrl::fromLocalFile("C:/Users/Behija/Desktop/Smart-Restaurant-2A28/music.mp3"));
    //music->play();
    ui->tableView_afficherCom->setModel(Com.Afficher_commande());
    ui->tableView_statCom->setModel(Com.Stat_commande());
    ui->tableView_statComStaff->setModel(Com.Stat_commandeStaff());
    ui->tableView_afficherPlat->setModel(P.Afficher_plat());

//Recherche Qcompleter
    QCompleter *completerCom = new QCompleter();
    completerCom->setModel(Com.rechercher_com());
    ui->lineEdit_rechercherCom->setCompleter(completerCom);

    QCompleter *completerPlat = new QCompleter();
    completerPlat->setModel(P.rechercher_plat2());
    ui->lineEdit_rechercherPlat->setCompleter(completerPlat);
//notification
    mysystem = new QSystemTrayIcon(this);
    mysystem->setVisible(true);

// controle de saisie
    ui->lineEdit_idPlat->setValidator(new QIntValidator(0,999999,this));
    ui->lineEdit_idPlat_2->setValidator(new QIntValidator(0,999999,this));
    ui->lineEdit_idclientB->setValidator(new QIntValidator(0,999999,this));
    ui->lineEdit_idclientB_2->setValidator(new QIntValidator(0,999999,this));
    ui->lineEdit_idcom->setValidator(new QIntValidator(0,999999,this));
    ui->lineEdit_idcomSup->setValidator(new QIntValidator(0,999999,this));
    ui->lineEdit_idcom_2->setValidator(new QIntValidator(0,999999,this));
    ui->lineEdit_idplatB->setValidator(new QIntValidator(0,999999,this));
    ui->lineEdit_idplatB_2->setValidator(new QIntValidator(0,999999,this));
    ui->lineEdit_idplatSup->setValidator(new QIntValidator(0,999999,this));
    ui->lineEdit_idstaffB->setValidator(new QIntValidator(0,999999,this));
    ui->lineEdit_idstaffB_2->setValidator(new QIntValidator(0,999999,this));
    ui->lineEdit_idtableB->setValidator(new QIntValidator(0,999999,this));
    ui->lineEdit_idtableB_2->setValidator(new QIntValidator(0,999999,this));
    ui->lineEdit_prixplat->setValidator(new QIntValidator(0,999999,this));
    ui->lineEdit_prixplat_2->setValidator(new QIntValidator(0,999999,this));
    //animation
        animation =new QPropertyAnimation(ui->pushButton_ajoutercom,"geometry");
        animation->setDuration(10000);
        animation->setStartValue(QRect(700, 500, 100, 15));
        animation->start();

    //arduino
      /*  int ret ;
        ret = A.connect_arduino();
        switch(ret)
        {
        case(0):
            qDebug() << "arduino is available and connected to :" << A.getarduino_port_name();
            break;
        case(1):
            qDebug() << "arduino is available but not connected to :" << A.getarduino_port_name();
            break;
        case(-1):
            qDebug() << "arduino is not available ";

        }
        QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Commandes
void MainWindow::on_pushButton_ajoutercom_clicked()
{
    click->play();
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
        //arduino
        //A.write_to_arduino(Com.afficher());
        qDebug() <<"le plat est :"<<Com.afficher();

        ui->tableView_afficherCom->setModel(Com.Afficher_commande());
        ui->tableView_statCom->setModel(Com.Stat_commande());
        ui->tabWidget_commande->setCurrentWidget(ui->afficherCom);

        ui->lineEdit_idcom->setText("");
        ui->lineEdit_typecom->setText("");
        ui->lineEdit_idstaffB->setText("");
        ui->lineEdit_idclientB->setText("");
        ui->lineEdit_idplatB->setText("");
        ui->lineEdit_idtableB->setText("");


        QMessageBox::information(nullptr, QObject::tr("Ajout validé"),QObject::tr("Ajout de la commande effectué.\n click cancel to exit."),QMessageBox::Cancel);
        mysystem->show();
        mysystem->showMessage(tr("notification"),tr("Ajout effectiué avec succés"));


    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajout non validé"),QObject::tr("Ajout de la commande non effectué.\n Verifier vos donnees ."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_annulerCom_clicked()
{
    click->play();
    ui->lineEdit_idcom->setText("");
    ui->lineEdit_typecom->setText("");
    ui->lineEdit_idstaffB->setText("");
    ui->lineEdit_idclientB->setText("");
    ui->lineEdit_idplatB->setText("");
    ui->lineEdit_idtableB->setText("");
}

void MainWindow::on_pushButton_modifierCom_clicked()
{
    click->play();
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
        QMessageBox ::critical(nullptr,QObject::tr("modifier une commande"),
                                          QObject::tr("Aucune selection.\n"
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
    click->play();
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
        ui->tableView_statComStaff->setModel(Com.Stat_commandeStaff());
        ui->lineEdit_idcom_2->setText("");
        ui->lineEdit_typecom_2->setText("");
        ui->lineEdit_idstaffB_2->setText("");
        ui->lineEdit_idclientB_2->setText("");
        ui->lineEdit_idplatB_2->setText("");
        ui->lineEdit_idtableB_2->setText("");
        QMessageBox::information(nullptr, QObject::tr("Modification validée"),QObject::tr("Modification de la commande effectuée.\n click cancel to exit."),QMessageBox::Cancel);
        mysystem->show();
        mysystem->showMessage(tr("notification"),tr("Modification effectiuée avec succés"));
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Modification non validée"),QObject::tr("Modification non effectuée.\n click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_supprimercom_clicked()
{
    click->play();
    QString ID_COM=ui->lineEdit_idcomSup->text();
    bool test=Com.Supprimer_commande(ID_COM);
    if(test && ui->lineEdit_idcomSup->text() != "")
    {
         ui->tableView_afficherCom->setModel(Com.Afficher_commande());
         ui->tableView_statCom->setModel(Com.Stat_commande());
         ui->tableView_statComStaff->setModel(Com.Stat_commandeStaff());
         ui->lineEdit_idcomSup->setText("");
        QMessageBox::information(nullptr, QObject::tr("suppression validée"),QObject::tr("suppression de la commande effectuée.\n click cancel to exit."),QMessageBox::Cancel);
        mysystem->show();
        mysystem->showMessage(tr("notification"),tr("Suppression effectiuée avec succés"));
        //hide();
       // S= new class Stat(this);
       // S.show();
    }
    else
       QMessageBox::critical(nullptr, QObject::tr("suppression non validée"),QObject::tr("suppression de la commande non effectuée.\n click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_rechercherCom_clicked()
{
    click->play();
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
    click->play();
    QPrinter printer;
     printer.setPrinterName("la commande");
     QPrintDialog dialog(&printer, this);
     if (dialog.exec() == QDialog::Rejected) return;
     ui->afficherCom->render(&printer);

}

void MainWindow::on_radioButton_triedateCom_clicked()
{
    click->play();
    ui->tableView_afficherCom->setModel(Com.trier_commandeDate());
}

void MainWindow::on_radioButton_trietypeCom_clicked()
{
    click->play();
    ui->tableView_afficherCom->setModel(Com.trier_commandeType());
}

void MainWindow::on_radioButton_trieidstaff_clicked()
{
    click->play();
    ui->tableView_afficherCom->setModel(Com.trier_commandeStaff());
}

//Plats
void MainWindow::on_pushButton_ajouterplat_clicked()
{
    click->play();
    QString ID_PLAT=ui->lineEdit_idPlat->text();
    QString NOM_PLAT=ui->lineEdit_nomplat->text();
    QString DESCRIPTION_PLAT=ui->lineEdit_descriptionplat->text();
    QString PRIX_PLAT=ui->lineEdit_prixplat->text();

    Plat P(ID_PLAT,NOM_PLAT,DESCRIPTION_PLAT,PRIX_PLAT);
    bool test=P.Ajouter_plat();
    if(test)
    {
        ui->tableView_afficherPlat->setModel(P.Afficher_plat());
        QMessageBox::information(nullptr, QObject::tr("Ajout validé"),QObject::tr("Ajout du plat effectué.\n click cancel to exit."),QMessageBox::Cancel);
        ui->tabWidget_Plat->setCurrentWidget(ui->afficherPlat);
        ui->lineEdit_idPlat->setText("");
        ui->lineEdit_nomplat->setText("");
        ui->lineEdit_descriptionplat->setText("");
        ui->lineEdit_prixplat->setText("");
        mysystem->show();
        mysystem->showMessage(tr("notification"),tr("Ajout effectiué avec succés"));
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajout non validé"),QObject::tr("Ajout du plat non effectué.\n verifier vos donnees."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_annulerPlat_clicked()
{
    click->play();
    ui->lineEdit_idPlat->setText("");
    ui->lineEdit_nomplat->setText("");
    ui->lineEdit_descriptionplat->setText("");
    ui->lineEdit_prixplat->setText("");
}

void MainWindow::on_pushButton_modifierPlat_clicked()
{
    click->play();
    int row=ui->tableView_afficherPlat->selectionModel()->currentIndex().row();
    QString ID_PLAT=ui->tableView_afficherPlat->model()->index(row,0).data().toString();
    QString NOM_PLAT=ui->tableView_afficherPlat->model()->index(row,1).data().toString();
    QString DESCRIPTION_PLAT=ui->tableView_afficherPlat->model()->index(row,2).data().toString();
    QString PRIX_PLAT=ui->tableView_afficherPlat->model()->index(row,3).data().toString();

    if(row==-1)
    {
        QMessageBox ::critical(nullptr,QObject::tr("modifier un plat"),
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
    click->play();
    QString ID_PLAT=ui->lineEdit_idPlat_2->text();
    QString NOM_PLAT=ui->lineEdit_nomplat_2->text();
    QString DESCRIPTION_PLAT=ui->lineEdit_descriptionplat_2->text();
    QString PRIX_PLAT=ui->lineEdit_prixplat_2->text();
    Plat P(ID_PLAT,NOM_PLAT,DESCRIPTION_PLAT,PRIX_PLAT);
    bool test=P.Modifier_plat();
    if(test)
    {
        ui->tableView_afficherPlat->setModel(P.Afficher_plat());
        ui->lineEdit_idPlat_2->setText("");
        ui->lineEdit_nomplat_2->setText("");
        ui->lineEdit_descriptionplat_2->setText("");
        ui->lineEdit_prixplat_2->setText("");
        QMessageBox::information(nullptr, QObject::tr("Modification validée"),QObject::tr("Modification du plat effectuée.\n click cancel to exit."),QMessageBox::Cancel);
        mysystem->show();
        mysystem->showMessage(tr("notification"),tr("Modification effectiuée avec succés"));
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Modification non validée"),QObject::tr("Modification du plat non effectuée.\n click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_supprimerplat_clicked()
{
    click->play();
    QString ID_PLAT=ui->lineEdit_idplatSup->text();
    bool test=P.Supprimer_plat(ID_PLAT);
    if(test && ui->lineEdit_idplatSup->text()!= "")
    {
         ui->tableView_afficherPlat->setModel(P.Afficher_plat());
         ui->lineEdit_idplatSup->setText("");
        QMessageBox::information(nullptr, QObject::tr("Suppression validée"),QObject::tr("Suppression du plat effectuée.\n click cancel to exit."),QMessageBox::Cancel);
        mysystem->show();
        mysystem->showMessage(tr("notification"),tr("Sppression effectiuée avec succés"));
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Suppression validée"),QObject::tr("Suppression du plat non effectuée.\n click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_imprimerPlat_clicked()
{
    click->play();
    QPrinter printer;
     printer.setPrinterName("les plats");
     QPrintDialog dialog(&printer, this);
     if (dialog.exec() == QDialog::Rejected) return;
     ui->tableView_afficherPlat->render(&printer);
}

void MainWindow::on_radioButton_trienomPlat_clicked()
{
    click->play();
    ui->tableView_afficherPlat->setModel(P.trier_platNom());
}

void MainWindow::on_radioButton_TriedesPlat_clicked()
{
    click->play();
    ui->tableView_afficherPlat->setModel(P.trier_platDescription());
}

void MainWindow::on_radioButton_trieprixPlat_clicked()
{
    click->play();
    ui->tableView_afficherPlat->setModel(P.trier_platPrix());
}

void MainWindow::on_pushButton_rechercherPlat_clicked()
{
    click->play();
    if(ui->lineEdit_rechercherPlat->text() == "")
        {
            ui->tableView_afficherPlat->setModel(P.Afficher_plat());
        }
    else
        {
             ui->tableView_afficherPlat->setModel(P.rechercher_plat(ui->lineEdit_rechercherPlat->text()));
        }

}



void MainWindow::on_pushButton_statCom_clicked()
{
    S.make();
    S.show();
}


/*
void liv::on_checkBox_7_clicked()
{
    if(ui->checkBox_7->isChecked())
    {
        ui->tabFour->setTabText(0,"ADD");
        ui->tabFour->setTabText(1,"DISPLAY");
        ui->ajouterFour->setText(tr("ADD"));
        ui->chercherFour->setText(tr("RESEARCH"));
        ui->label_gestionDesFour->setText(tr("Management Of Suppliers"));
        ui->lineEdit_nom->setText(tr("SURNAME"));
        ui->lineEdit_idFour->setText(tr("ID"));
        ui->lineEdit_modifierId->setText(tr("ID"));
        ui->lineEdit_modifierNom->setText(tr("SURNAME"));
        ui->lineEdit_modifierPrenom->setText(tr("NAME"));
        ui->lineEdit_numTel->setText(tr("Phone num"));
        ui->pushButton_imprimerFour->setText(tr("PRINT"));
        ui->pushButton_modifierFour->setText(("UPDATE"));
        ui->supprimerFour->setText(tr("DELETE"));
        ui->radioButton->setText(tr("refresh"));
        ui->label->setText(tr("sort by name"));
        ui->label_2->setText(tr("sort by id"));
        ui->lineEdit_suppidFour->setText(tr("ID /CIN/ NAME"));
        ui->goToLiv->setText(tr("Delivery Management"));
        ui->lineEdit_prenom->setText(tr("NAME"));
        ui->lineEdit_emailFour->setText(tr("E-mail"));
        ui->lineEdit_modifierEmail->setText(tr("E-mail"));
        ui->lineEdit_modifierCin->setText(tr("CIN"));
        ui->lineEdit_cinPerso->setText(tr("CIN"));
        ui->pushButton->setText(tr("ON"));
        ui->pushButton_2->setText(tr("OFF"));
        ui->lineEdit_modifierNum->setText(tr("Phone num"));
        ui->checkBox_7->setText(tr("Frensh Version"));
    }

else
        {
            ui->tabFour->setTabText(0,"AJOUTER");
            ui->tabFour->setTabText(1,"AFFICHER");
            ui->ajouterFour->setText(tr("AJOUTER"));
            ui->chercherFour->setText(tr("CHERCHER"));
            ui->label_gestionDesFour->setText(tr("Gestion Des Fournisseurs"));
            ui->lineEdit_nom->setText(tr("NOM"));
            ui->lineEdit_idFour->setText(tr("ID"));
            ui->lineEdit_modifierId->setText(tr("ID"));
            ui->lineEdit_modifierNom->setText(tr("NOM"));
            ui->lineEdit_modifierPrenom->setText(tr("PRENOM"));
            ui->lineEdit_numTel->setText(tr("numTel"));
            ui->pushButton_imprimerFour->setText(tr("IMPRIMER"));
            ui->pushButton_modifierFour->setText(("MODIFIER"));
            ui->supprimerFour->setText(tr("SUPPRIMER"));
            ui->radioButton->setText(tr("actualiser"));
            ui->label->setText(tr("tri par nom"));
            ui->label_2->setText(tr("tri par id"));
            ui->lineEdit_suppidFour->setText(tr("ID /CIN/ NOM"));
            ui->goToLiv->setText(tr("Gestion De Livraison"));
            ui->lineEdit_prenom->setText(tr("PRENOM"));
            ui->lineEdit_emailFour->setText(tr("E-mail"));
            ui->lineEdit_modifierEmail->setText(tr("E-mail"));
            ui->lineEdit_modifierCin->setText(tr("CIN"));
            ui->lineEdit_cinPerso->setText(tr("CIN"));
            ui->pushButton->setText(tr("ON"));
            ui->pushButton_2->setText(tr("OFF"));
            ui->lineEdit_modifierNum->setText(tr("NumTel"));
            ui->checkBox_7->setText(tr("Version Anglais"));


        }



    }*/


void MainWindow::on_checkBox_traduction_clicked()
{
    if(ui->checkBox_traduction->isChecked())
    {
        ui->pushButton_ajoutercom->setText(tr("Add"));
        ui->pushButton_ajouterplat->setText(tr("Add"));
        ui->pushButton_annulerCom->setText(tr("Cancel"));
        ui->pushButton_annulerPlat->setText(tr("Cancel"));
        ui->pushButton_imprimerCom->setText(tr("Print"));
        ui->pushButton_imprimerPlat->setText(tr("Print"));
        ui->pushButton_modifierCom->setText(tr("Modify"));
        ui->pushButton_modifierPlat->setText(tr("Modify"));
        ui->pushButton_rechercherCom->setText(tr("Search"));
        ui->pushButton_rechercherPlat->setText(tr("Search"));
        ui->pushButton_statCom->setText(tr("Statistic"));
        ui->pushButton_supprimercom->setText(tr("Remove"));
        ui->pushButton_supprimerplat->setText(tr("Remove"));
        ui->pushButton_vaModificationCom->setText(tr("Validate the modification"));
        ui->pushButton_vaModificationPlat->setText(tr("Validate the modification"));
        ui->label_afficherCom->setText(tr("Display orders"));
        ui->label_afficherPlat->setText(tr("Display dishs"));
        ui->label_ajouterCom->setText(tr("Add an order"));
        ui->label_ajouterPlat->setText(tr("Add a dish"));
        ui->label_dateCom->setText(tr("Date"));
        ui->label_dateCom_2->setText(tr("Date"));
        ui->label_descriptionPlat->setText(tr("Description"));
        ui->label_descriptionPlat_2->setText(tr("Description"));
        ui->label_idClientB->setText(tr("Customer id"));
        ui->label_idClientB_2->setText(tr("Customer id"));
        ui->label_idCom->setText(tr("Order id"));
        ui->label_idComSupp->setText(tr("Order id"));
        ui->label_idCom_2->setText(tr("Order id"));
        ui->label_idPlat->setText(tr("Dish id"));
        ui->label_idPlatB_2->setText(tr("Dish id"));
        ui->label_idPlatSupp->setText(tr("Dish id"));
        ui->label_idPlat_2->setText(tr("Dish id"));
        ui->label_idStaffB_2->setText(tr("Staff id"));
        ui->label_idTableB->setText(tr("Table id"));
        ui->label_idTableB_2->setText(tr("Table id"));
        ui->label_idplatB->setText(tr("Dish id"));
        ui->label_idstaffB->setText(tr("Staff id"));
        ui->label_nomPlat->setText(tr("Dish name"));
        ui->label_nomPlat_2->setText(tr("Dish name"));
        ui->label_prixPlat->setText(tr("Dish price"));
        ui->label_prixPlat_2->setText(tr("Dish price"));
        ui->label_typeCom->setText(tr("Order type"));
        ui->label_typeCom_2->setText(tr("Order type"));
        ui->radioButton_TriedesPlat->setText(tr("Sort description"));
        ui->radioButton_triedateCom->setText(tr("sort date"));
        ui->radioButton_trieidstaff->setText(tr("Sort staff id"));
        ui->radioButton_trienomPlat->setText(tr("Sort dish name"));
        ui->radioButton_trieprixPlat->setText(tr("Sort dish price"));
        ui->radioButton_trietypeCom->setText(tr("Sort order type"));
        ui->checkBox_traduction->setText(tr("Frensh Version"));

    }
    else
    {
        ui->pushButton_ajoutercom->setText(tr("Ajouter"));
        ui->pushButton_ajouterplat->setText(tr("Ajouter"));
        ui->pushButton_annulerCom->setText(tr("Annuler"));
        ui->pushButton_annulerPlat->setText(tr("Annuler"));
        ui->pushButton_imprimerCom->setText(tr("Imprimer"));
        ui->pushButton_imprimerPlat->setText(tr("Imprimer"));
        ui->pushButton_modifierCom->setText(tr("Modifier"));
        ui->pushButton_modifierPlat->setText(tr("Modifier"));
        ui->pushButton_rechercherCom->setText(tr("Recherche"));
        ui->pushButton_rechercherPlat->setText(tr("Recherche"));
        ui->pushButton_statCom->setText(tr("Statistique"));
        ui->pushButton_supprimercom->setText(tr("Supprimer"));
        ui->pushButton_supprimerplat->setText(tr("Supprimer"));
        ui->pushButton_vaModificationCom->setText(tr("Valider la modification"));
        ui->pushButton_vaModificationPlat->setText(tr("Valider la modification"));
        ui->label_afficherCom->setText(tr("Afficher les commandes"));
        ui->label_afficherPlat->setText(tr("Afficher les plats"));
        ui->label_ajouterCom->setText(tr("Ajouter une commande"));
        ui->label_ajouterPlat->setText(tr("Ajouter un plat"));
        ui->label_dateCom->setText(tr("Date"));
        ui->label_dateCom_2->setText(tr("Date"));
        ui->label_descriptionPlat->setText(tr("Description"));
        ui->label_descriptionPlat_2->setText(tr("Description"));
        ui->label_idClientB->setText(tr("Id client"));
        ui->label_idClientB_2->setText(tr("Id client"));
        ui->label_idCom->setText(tr("Id commande"));
        ui->label_idComSupp->setText(tr("Id commande"));
        ui->label_idCom_2->setText(tr("Id commande"));
        ui->label_idPlat->setText(tr("Id plat"));
        ui->label_idPlatB_2->setText(tr("Id plat"));
        ui->label_idPlatSupp->setText(tr("Id plat"));
        ui->label_idPlat_2->setText(tr("Id plat"));
        ui->label_idStaffB_2->setText(tr("Id personnel"));
        ui->label_idTableB->setText(tr("Id table"));
        ui->label_idTableB_2->setText(tr("Id table"));
        ui->label_idplatB->setText(tr("Id plat"));
        ui->label_idstaffB->setText(tr("Id personnel"));
        ui->label_nomPlat->setText(tr("Nom du plat"));
        ui->label_nomPlat_2->setText(tr("Nom du Plat"));
        ui->label_prixPlat->setText(tr("Prix du plat"));
        ui->label_prixPlat_2->setText(tr("Prix du plat"));
        ui->label_typeCom->setText(tr("Type de commande"));
        ui->label_typeCom_2->setText(tr("Type de commande"));
        ui->radioButton_TriedesPlat->setText(tr("Trier description"));
        ui->radioButton_triedateCom->setText(tr("Trier date"));
        ui->radioButton_trieidstaff->setText(tr("Trier id personnel"));
        ui->radioButton_trienomPlat->setText(tr("Trier nom du plat"));
        ui->radioButton_trieprixPlat->setText(tr("Trier prix du plat"));
        ui->radioButton_trietypeCom->setText(tr("Trier type de commande"));
        ui->checkBox_traduction->setText(tr("Version anglaise"));
        //ui->Commande->setWindowIconName(tr("Order"));
    }
}

//arduino

void MainWindow::update_label()
{
    data=A.read_from_arduino();
    if(data == "1")
    {
        ui->label_afficherCom->setText("la commande est envoyée");
    }
    else if (data == "0")
    {
        ui->label_afficherCom->setText("la commande n'est pas envoyée");
    }
}
