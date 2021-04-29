#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "client.h"
#include "ajouterres.h"
#include "modifierres.h"
#include "supprimerres.h"
#include "tables.h"
#include "ajoutertab.h"
#include "modifiertab.h"
#include "supprimertab.h"
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include "smtp.h"
#include <QDebug>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QtPrintSupport>
Connection1::Connection1(){}

bool Connection1::createconnection1()
{
    bool test=false;
    QSqlDatabase db1 = QSqlDatabase::addDatabase("QODBC");
    db1.setDatabaseName("smart_restaurant");//inserer le nom de la source de données ODBC
    db1.setUserName("behija");//inserer nom de l'utilisateur
    db1.setPassword("behija");//inserer mot de passe de cet utilisateur

    if (db1.open())
    test=true;
    return  test;
}

void Connection1::closeconnection1(){db1.close();}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     ui->stackedWidget->setCurrentIndex(0);
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
    int regio;
   int non_regio;
   int total;
   QString regionale;
   QString non_regionale;
   QSqlQuery q;

   q.prepare("SELECT COUNT(id_com) FROM commandes where type_com='livraison' ");
   q.exec();
   q.first() ;
   regio=(q.value(0).toInt());

   q.prepare("SELECT COUNT(id_com) FROM commandes where type_com='sur place' ");
   q.exec();
   q.first() ;
   non_regio=(q.value(0).toInt());

   q.prepare("SELECT COUNT(id_com) FROM commandes ");
   q.exec();
   q.first() ;
   total=(q.value(0).toInt());

   regio=((double)regio/(double)total)*100;
   non_regio=100-regio;

   regionale= QString::number(regio);
   non_regionale=QString::number(non_regio);
   QPieSeries *series;
    series= new  QPieSeries();
    series->append("livraison"+regionale+"%",regio);
    series->append("sur place"+non_regionale+"%",non_regio);
    QPieSlice *slice0 = series->slices().at(0);
     slice0->setLabelVisible();

     QPieSlice *slice1 = series->slices().at(1);
        slice1->setExploded();
        slice1->setLabelVisible();
        slice1->setPen(QPen(Qt::green, 3));
        slice1->setBrush(Qt::darkYellow);

         QChart *chart = new QChart();
         chart->addSeries(series);
         chart->setTitle("Statistique du type de commandes ");
         chart->legend()->show();
         QChartView *chartView = new QChartView(chart);
         chartView->setRenderHint(QPainter::Antialiasing);
         ui->verticalLayout->addWidget(chartView);
    show();
    //ui->
}




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




void MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file_3->setText( fileListString );

}


void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname_3->text(), ui->paswd_3->text(), ui->server_3->text(), ui->port_3->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(ui->uname_3->text(), ui->rcpt_3->text() , ui->subject_3->text(),ui->msg_3->toPlainText(), files );
    else
        smtp->sendMail(ui->uname_3->text(), ui->rcpt_3->text() , ui->subject_3->text(),ui->msg_3->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}


//~Mailing

void MainWindow::on_pushButton_ajouterres_2_clicked()
{
    ajouterres ajouter;
    ajouter.setModal(true);
    ajouter.exec();

    Connection1 conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db1);
    qry->prepare("select * from reservation");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_res_2->setModel(modal);

}

void MainWindow::on_pushButton_modifierres_2_clicked()
{
    modifierres modifier;
    modifier.setModal(true);
    modifier.exec();

    Connection1 conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db1);
    qry->prepare("select * from reservation");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_res_2->setModel(modal);
}

void MainWindow::on_pushButton_supprimerres_2_clicked()
{
    supprimerres supp;
    supp.setModal(true);
    supp.exec();

    Connection1 conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db1);
    qry->prepare("select * from reservation");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_res_2->setModel(modal);
}


void MainWindow::on_pushButton_chercherres_2_clicked()
{

            QString CIN= ui->lineEdit_3->text() ;
            ui->tableView_res_2->setModel(tempclient.cherchercinres(CIN));


}


void MainWindow::on_radioButton_tricin_2_clicked()
{
    Connection1 conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db1);
    qry->prepare("select * from reservation ORDER BY CIN ");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_res_2->setModel(modal);
}

void MainWindow::on_pushButton_listeres_2_clicked()
{
      ui->tableView_res_2->setModel(tempclient.afficherres());
}

void MainWindow::on_radioButton_triprenom_2_clicked()
{
    Connection1 conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db1);
    qry->prepare("select * from reservation ORDER BY Prenom");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_res_2->setModel(modal);
}

void MainWindow::on_radioButton_trinom_2_clicked()
{
    Connection1 conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db1);
    qry->prepare("select * from reservation ORDER BY Nom");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_res_2->setModel(modal);
}


void MainWindow::on_pushButton_table_2_clicked()
{
ui->tableView_table_2->setModel(temptable.affichertab());
}

void MainWindow::on_pushButton_ajoutertab_2_clicked()
{
    ajoutertab ajouter;
    ajouter.setModal(true);
    ajouter.exec();

    Connection1 conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db1);
    qry->prepare("select * from tables");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_table_2->setModel(modal);
}

void MainWindow::on_pushButton_modifiertab_2_clicked()
{
    modifiertab modifier;
    modifier.setModal(true);
    modifier.exec();

    Connection1 conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db1);
    qry->prepare("select * from tables");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_table_2->setModel(modal);
}

void MainWindow::on_pushButton_supprimertab_2_clicked()
{
    supprimertab supp;
    supp.setModal(true);
    supp.exec();

    Connection1 conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db1);
    qry->prepare("select * from tables");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_table_2->setModel(modal);

}

void MainWindow::on_sendBtn_3_clicked()
{
        connect(ui->sendBtn_3, SIGNAL(clicked()),this, SLOT(sendMail()));
        connect(ui->exitBtn_3, SIGNAL(clicked()),this, SLOT(close()));
        connect(ui->browseBtn_4, SIGNAL(clicked()), this, SLOT(browse()));

}

void MainWindow::on_pushButton_mail_2_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(1);

}

void MainWindow::on_pushButton_retour_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}





void MainWindow::on_pushButton_res_2_clicked()
{
    QPrinter printer;
        printer.setPrinterName("diserter printer name");
        QPrintDialog dialog(&printer,this);
        if(dialog.exec()==QDialog::Rejected)return;
        ui->tableView_res_2->render(&printer);
}

void MainWindow::on_pushButton_cherchertab_2_clicked()
{
    QString Numero= ui->lineEdit_4->text() ;

    ui->tableView_table_2->setModel(temptable.cherchertable(Numero));
}






void MainWindow::on_pushButton_gestioncom_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_gestionres_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}



void MainWindow::on_pushButton_retourCom_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_retour_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


