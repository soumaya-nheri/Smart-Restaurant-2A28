#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "ajouterres.h"
#include "conge.h"
#include <QPrinter>
#include <QFileDialog>
#include <smtp.h>
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
    conge tmpconge;
    ui->setupUi(this);
     ui->stackedWidget->setCurrentIndex(0);
     ui->tableView_staff_2->setModel(tmpstaff.afficher());
     QSqlQueryModel * modell = tmpconge.afficher();
     ui->tableViewConge_2->setModel( modell);
     ui->tableView_staff_2->setSelectionBehavior(QAbstractItemView::SelectRows);
     ui->tableView_staff_2->setSelectionMode(QAbstractItemView::SingleSelection);
     QSqlQueryModel *model2=new QSqlQueryModel();
     QSqlQueryModel *model3=new QSqlQueryModel();
     model3->setQuery("select email from staff");
     QString nom;
     model2->setQuery("select nom from staff");
     ui->comboBox_employe_2->setModel(model2);
     ui->comboBox_2->setModel(model3);

     //music
        click = new QMediaPlayer();
        click->setMedia(QUrl::fromLocalFile("C:/Users/dedpy/Desktop/GIT-Qt/integration/Click.wav"));
        music = new QMediaPlayer();
        music->setMedia(QUrl::fromLocalFile("C:/Users/dedpy/Desktop/GIT-Qt/integration/music.mp3"));
        music->play();
        ui->tableView_afficherCom->setModel(Com.Afficher_commande());
        ui->tableView_statCom->setModel(Com.Stat_commande());
        ui->tableView_statComStaff->setModel(Com.Stat_commandeStaff());
        ui->tableView_afficherPlat->setModel(P.Afficher_plat());
    //statistique
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
            ui->verticalLayout->removeWidget(chartView);
    //Recherche Qcompleter
        QStringList wordList;
            qry.exec("SELECT id_com, type_com, id_plat FROM commandes");
            while(qry.next()){
            wordList.push_back(qry.value(0).toString());
            wordList.push_back(qry.value(1).toString());
            wordList.push_back(qry.value(2).toString());
            }
            qDebug()<<wordList;
            QCompleter *completer = new QCompleter(wordList, this);
            completer->setCaseSensitivity(Qt::CaseInsensitive);
            ui->lineEdit_rechercherCom->setCompleter(completer);

            QStringList wordList1;

            qry1.exec("SELECT nom_plat, description_plat, prix_plat FROM plats");
            while(qry1.next()){
            wordList1.push_back(qry1.value(0).toString());
            wordList1.push_back(qry1.value(1).toString());
            wordList1.push_back(qry1.value(2).toString());
            }
            qDebug()<<wordList1;
            QCompleter *completer1 = new QCompleter(wordList1, this);
            completer1->setCaseSensitivity(Qt::CaseInsensitive);
            ui->lineEdit_rechercherPlat->setCompleter(completer1);
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


void MainWindow::on_ajouter_staff_2_clicked()
{
    QString cin=ui->cin_staff_2->text();
    QString nom=ui->nom_staff_2->text();
    QString prenom=ui->prenom_staff_2->text();
    QString email=ui->email_staff_2->text();
    QString telephone=ui->tel_staff_2->text();
    QString login=ui->login_staff_2->text();
    QString password=ui->pass_staff_2->text();
    QString role=ui->role_staff_2->currentText();
    int salaire=ui->salaire_staff_2->text().toInt();

    staff staff(cin,nom,prenom,email,telephone,login,password,role,salaire);
    if (staff.ajouter())
    {
        ui->tableView_staff_2->setModel(tmpstaff.afficher());

    }
    else
    {
        qDebug() << "Erreur d'ajout.";
    }
    QSqlQueryModel *model2=new QSqlQueryModel();
    QString s;
    model2->setQuery("select nom from staff");
    ui->comboBox_employe_2->setModel(model2);
    ui->comboBox_2->setModel(model2);
}

void MainWindow::on_modifier_staff_2_clicked()
{
    if (ui->modifier_staff_2->isChecked())
    {
        ui->modifier_staff_2->setText(tr("Modifiable"));
        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("STAFF");
        tableModel->select();
        ui->tableView_staff_2->setModel(tableModel);
    }
    else
    {
        ui->modifier_staff_2->setText(tr("Modifier"));
        ui->tableView_staff_2->setModel(tmpstaff.afficher());
    }
}

void MainWindow::on_supprimer_staff_2_clicked()
{
    QItemSelectionModel *select = ui->tableView_staff_2->selectionModel();

    QString cin =select->selectedRows(0).value(0).data().toString();

    if(tmpstaff.supprimer(cin))
    {
        ui->tableView_staff_2->setModel(tmpstaff.afficher());

    }

}

void MainWindow::on_ajouter_2_clicked()
{
    conge tmpconge;
        if(ui->lineEditNumConge_2->text()!=""){
        QString id=ui->lineEditNumConge_2->text();
        /*QString nom=ui->lineEditType->text();*/
        QString nom=ui->comboBox_employe_2->currentText();
        QString dated=ui->dateEditDebut_2->date().toString();
        QString datef=ui->dateEditFin_2->date().toString();
        QString type=ui->comboBoxType_2->currentText();

        conge conge(id, nom, dated, datef, type);
        conge.ajouter();
        QSqlQueryModel * modell = tmpconge.afficher();
        ui->tableViewConge_2->setModel( modell);
        QSortFilterProxyModel *mm=new QSortFilterProxyModel(this);
           mm->setDynamicSortFilter(true);
           mm->setSourceModel(modell);
           ui->tableViewConge_2->setModel(mm);
           ui->tableViewConge_2->setSortingEnabled(true);
        foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
            widget->clear();
        }
    }
}


void MainWindow::on_pushButtonSuppr_2_clicked()
{
    conge tmpconge;


    QItemSelectionModel *select = ui->tableViewConge_2->selectionModel();
        QString idstaff =select->selectedRows(0).value(0).data().toString();
        if(tmpconge.supprimer(idstaff))
            {
               QSqlQueryModel * modell = tmpconge.afficher();
               ui->tableViewConge_2->setModel( modell);
               QSortFilterProxyModel *mm=new QSortFilterProxyModel(this);
               mm->setDynamicSortFilter(true);
               mm->setSourceModel(modell);
               ui->tableViewConge_2->setModel(mm);
               ui->tableViewConge_2->setSortingEnabled(true);
            }
}

void MainWindow::on_pushButtonEdit_2_clicked()
{
    if (ui->pushButtonEdit_2->isChecked())

                {

                    ui->pushButtonEdit_2->setDisabled(true);

                    ui->pushButtonEdit_2->setText("Modifiable");

                    QSqlTableModel *tableModel= new QSqlTableModel();

                    tableModel->setTable("CONGE");

                    tableModel->select();

                    ui->tableViewConge_2->setModel(tableModel);

                }

                else

                {

                    ui->pushButtonEdit_2->setText("Modifier");QSqlQueryModel * model = tmpstaff.afficher();

                    ui->tableView_staff_2->setModel( model);

                    QSortFilterProxyModel *m=new QSortFilterProxyModel(this);

                    m->setDynamicSortFilter(true);

                    m->setSourceModel(model);

                    ui->tableViewConge_2->setModel(m);

                    ui->tableViewConge_2->setSortingEnabled(true);

                }

    ui->pushButtonEdit_2->setChecked(false);
}

void MainWindow::on_pushButtonPDF_3_clicked()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
                    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append("Liste Des Employés.pdf"); }

                    QPrinter printer(QPrinter::PrinterResolution);
                    printer.setOutputFormat(QPrinter::PdfFormat);
                    printer.setPaperSize(QPrinter::A4);
                    printer.setOutputFileName(fileName);

                    QTextDocument doc;
                    QSqlQuery q;
                    q.prepare("SELECT * FROM conge ");
                    q.exec();
                    QString pdf="<br><br><img src='A:/me.jpg' height='42' align='left' width='42'/>  <h1 align='middle' style='color:blue;   style='display: block;margin: auto;max-width: 600px;padding:5px;width: 100%;'>LISTE DES staffS  <><br></h1>\n <br> <table  style='border: 1px solid black;background: white; border-radius:3px; border-collapse: collapse; margin: auto;  padding:5px; width: 100%; box-shadow: 0 5px 10px rgba(0, 0, 0, 0.1);'>  <tr>  <th style='border: 1px solid black;color:#D5DDE5;background:#1b1e24;border-bottom:4px solid #9ea7af;border-right: 1px solid #343a45;font-size:12px;font-weight: 100;padding:24px;text-align:left;text-shadow: 0 1px 1px rgba(0, 0, 0, 0.1);vertical-align:middle;'>ID </th> <th style='border: 1px solid black;color:#D5DDE5;background:#1b1e24;border-bottom:4px solid #9ea7af;border-right: 1px solid #343a45;font-size:12px;font-weight: 100;padding:24px;text-align:left;text-shadow: 0 1px 1px rgba(0, 0, 0, 0.1);vertical-align:middle;'>staff </th> <th style='border: 1px solid black;color:#D5DDE5;background:#1b1e24;border-bottom:4px solid #9ea7af;border-right: 1px solid #343a45;font-size:12px;font-weight: 100;padding:24px;text-align:left;text-shadow: 0 1px 1px rgba(0, 0, 0, 0.1);vertical-align:middle;'>Date de debut </th> <th style='border: 1px solid black;color:#D5DDE5;background:#1b1e24;border-bottom:4px solid #9ea7af;border-right: 1px solid #343a45;font-size:12px;font-weight: 100;padding:12px;text-align:left;text-shadow: 0 1px 1px rgba(0, 0, 0, 0.1);vertical-align:middle;'> Date de fin </th> <th style='border: 1px solid black;color:#D5DDE5;background:#1b1e24;border-bottom:4px solid #9ea7af;border-right: 1px solid #343a45;font-size:12px;font-weight: 100;padding:12px;text-align:left;text-shadow: 0 1px 1px rgba(0, 0, 0, 0.1);vertical-align:middle;border: 1px solid black;'>type</th>  </tr>";


                    while ( q.next()) {

                        pdf= pdf+ " <br> <tr style='border-top: 1px solid #C1C3D1; border-bottom-: 1px solid #C1C3D1; color:#666B85;padding-bottom:5px; font-size:16px; font-weight:normal; text-shadow: 0 1px 1px rgba(256, 256, 256, 0.1);'> <td style='border: 1px solid black;border: 1px solid black;background:#FFFFFF; padding:20px; text-align:left; vertical-align:middle; font-weight:300; font-size:8px; text-shadow: -1px -1px 1px rgba(0, 0, 0, 0.1); border-right: 1px solid #C1C3D1;'>"+ q.value(0).toString()+"</td>  <td style='border: 1px solid black;border: 1px solid black;background:#FFFFFF; padding:20px; text-align:left; vertical-align:middle; font-weight:300; font-size:8px; text-shadow: -1px -1px 1px rgba(0, 0, 0, 0.1); border-right: 1px solid #C1C3D1;'> " + q.value(1).toString() +"</td>   <td style='border: 1px solid black;background:#FFFFFF; padding:20px; text-align:left; vertical-align:middle; font-weight:300; font-size:8px; text-shadow: -1px -1px 1px rgba(0, 0, 0, 0.1); border-right: 1px solid #C1C3D1;'>" +q.value(2).toString() +"  "" " "</td>   <td style='border: 1px solid black;background:#FFFFFF; padding:20px; text-align:left; vertical-align:middle; font-weight:300; font-size:8px; text-shadow: -1px -1px 1px rgba(0, 0, 0, 0.1); border-right: 1px solid #C1C3D1;'>"+q.value(3).toString()+"</td>   <td style='border: 1px solid black;background:#FFFFFF; padding:20px; text-align:left; vertical-align:middle; font-weight:300; font-size:8px; text-shadow: -1px -1px 1px rgba(0, 0, 0, 0.1); border-right: 1px solid #C1C3D1;'>"+q.value(4).toString()+" "  " " "</td> </td>" ;

                    }
                    doc.setHtml(pdf);
                    doc.setPageSize(printer.pageRect().size()); // t5abbi numero l page
                    doc.print(&printer);
}

/*
void MainWindow::on_ajouter_planning_clicked()
{
    QString nom=ui->nom_staff->text();
    QString prenom=ui->prenom_staff->text();
    QDateTimeEdit DATE_PRESENCE=ui->DATE_PRESENCE->text();
    QString telephone=ui->tel_staff->text();
    QString login=ui->login_staff->text();
    QString password=ui->pass_staff->text();
    QString role=ui->role_staff->currentText();
    int salaire=ui->salaire_staff->text().toInt();

    planning planning(cin,nom,prenom,email,telephone,login,password,role,salaire);
    if (planning.ajouter())
    {
        ui->tableView_planning->setModel(tmpstaff.afficher());

    }
    else
    {
        qDebug() << "Erreur d'ajout.";
    }
}*/

/*
void MainWindow::on_rechercher_staff_clicked()
{
    ui->tableView_staff->setModel(tempstaff.recherchestaff(arg1));
}*/

void MainWindow::on_recherche_staff_2_textChanged(const QString &arg1)
{
    ui->tableView_staff_2->setModel(tmpstaff.rechercher(arg1));
}

void MainWindow::on_rechercher_staff_2_clicked()
{
    QString nom=ui->recherche_staff_2->text();
    QSqlQueryModel *verif_nom=tmpstaff.recherchestaff(nom);
    if (verif_nom!=nullptr)
    {
        ui->tableView_staff_2->setModel(verif_nom);
    }
}

void MainWindow::on_ajouter_planning_2_clicked()
{

    planning p("x",ui->DATE_PRESENCE_2->date(),ui->NB_HEURE_2->text().toInt(),ui->comboBox_2->currentText());
    bool test=p.ajouter();
    if (test)
         ui->tableView_planning_2->setModel(tmplanning.afficher());
}

void MainWindow::on_pushButtonRechercherConge_2_clicked()
{
    {

        conge e;

            QString text;

            if (ui->radioButton_ID_2->isChecked()==true)

        {

        text=ui->line_recherche_critere_2->text();

             if(text == "")


             {


                 ui->tableViewConge_2->setModel(e.afficher());


             }


             else


             {




                 ui->tableViewConge_2->setModel(e.chercher_emp(text));


             }

            }


             else if     (ui->radioButton_nom_2->isChecked()==true)

             {


                 text=ui->line_recherche_critere_2->text();

                      if(text == "")


                      {


                          ui->tableViewConge_2->setModel(e.afficher());



                      }


                      else


                      {




                          ui->tableViewConge_2->setModel(e.chercher_emp2(text));


                      }

             }
}
}

void MainWindow::on_pushButton_2_clicked()
{
    click->play();
    Smtp* smtp = new Smtp("dedsec1450@gmail.com", "wassimben123", "smtp.gmail.com", 465);
    smtp->sendMail("Qt projet esprit", ui->comboBox_2->currentText() ,"Planning"," du votre seance de travaille : "+ui->DATE_PRESENCE_2->date().toString("dddd, dd MMMM yyyy"));
}

void MainWindow::on_supprimer_planning_2_clicked()
{
    QItemSelectionModel *select = ui->tableView_planning_2->selectionModel();

    QString date_presence =select->selectedRows(0).value(0).data().toString();

    if(tmplanning.supprimer(date_presence))
    {
        ui->tableView_planning_2->setModel(tmplanning.afficher());

    }

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

            ui->verticalLayout->removeWidget(chartView);

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

            ui->verticalLayout->removeWidget(chartView);
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

            ui->verticalLayout->removeWidget(chartView);

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
   click->play();
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
    click->play();
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
    click->play();
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
    click->play();
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
            click->play();
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
    click->play();
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
    click->play();
ui->tableView_table_2->setModel(temptable.affichertab());
}

void MainWindow::on_pushButton_ajoutertab_2_clicked()
{
    click->play();
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
    click->play();
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
    click->play();
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
    click->play();
    ui->stackedWidget_3->setCurrentIndex(1);

}

void MainWindow::on_pushButton_retour_6_clicked()
{
    click->play();
    ui->stackedWidget->setCurrentIndex(0);
}





void MainWindow::on_pushButton_res_2_clicked()
{
    click->play();
    QPrinter printer;
        printer.setPrinterName("diserter printer name");
        QPrintDialog dialog(&printer,this);
        if(dialog.exec()==QDialog::Rejected)return;
        ui->tableView_res_2->render(&printer);
}

void MainWindow::on_pushButton_cherchertab_2_clicked()
{
    click->play();
    QString Numero= ui->lineEdit_4->text() ;

    ui->tableView_table_2->setModel(temptable.cherchertable(Numero));
}






void MainWindow::on_pushButton_gestioncom_clicked()
{
    click->play();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_gestionres_clicked()
{
    click->play();
    ui->stackedWidget->setCurrentIndex(2);
}



void MainWindow::on_pushButton_retourCom_clicked()
{
    click->play();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_retour_3_clicked()
{
    click->play();
    ui->stackedWidget->setCurrentIndex(0);
}



void MainWindow::on_pushButton_gestionstaff_clicked()
{
    click->play();
    ui->stackedWidget->setCurrentIndex(3);
}

