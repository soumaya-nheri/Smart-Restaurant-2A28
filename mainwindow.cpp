#include "mainwindow.h"
#include "mainwindow0.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "ajouterres.h"
#include "conge.h"
#include "produit.h"
#include<fclient.h>
#include<flivraison.h>
#include "ajouterproduit.h"
#include "modifierproduit.h"
#include "supprimerproduit.h"
#include "fournisseur.h"
#include "ajouter_fournisseur.h"
#include "modifier_fournisseur.h"
#include "supprimer_fournisseur.h"
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
    db1.setDatabaseName("Source_Projet2A");
    db1.setUserName("Wassim");
    db1.setPassword("esprit18");

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
    this->setWindowTitle("Smart Restaurant");
    ui->tableView->setModel(tmpclient.afficher());//refresh
    ui->tableView_2->setModel(tmplivraison.afficher());//refresh
    mysystem1 = new QSystemTrayIcon(this);
    mysystem1->setVisible(true);
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
             show();

     //music
        click = new QMediaPlayer();
        click->setMedia(QUrl::fromLocalFile("C:/Users/dedpy/Desktop/GIT-Qt/integration/Click.wav"));
        music = new QMediaPlayer();
        music->setMedia(QUrl::fromLocalFile("C:/Users/dedpy/Desktop/GIT-Qt/integration/music.mp3"));
        //music->play();
        ui->tableView_afficherCom->setModel(Com.Afficher_commande());
        ui->tableView_statCom->setModel(Com.Stat_commande());
        ui->tableView_statComStaff->setModel(Com.Stat_commandeStaff());
        ui->tableView_afficherPlat->setModel(P.Afficher_plat());

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


        //bacim
            QIntValidator *roll = new QIntValidator(100000,999999);
                ui->pushButton_10->hide();
                ui->plainTextEdit_2->hide();

                ui->lineEditId_4->setValidator(roll);
                ui->lineEditIdOffre_4->setValidator(roll);
                ui->tableView_7->setModel(evenementtmp.show_evenements());
                 ui->tableView_8->setModel(offretmp.show_offres());
                QFile file1("C:/Users/dedpy/Desktop/Historique.txt");
               if (!file1.open(QIODevice::ReadOnly))
               {
                   QMessageBox::information(0,"info",file1.errorString());
               }
               QTextStream in (&file1);
              ui->textBrowser_4->setText(in.readAll());

                ui->tabWidget1->setCurrentIndex(0);
                QPieSeries *series_1 = new QPieSeries();
                    QSqlQuery qq("select prix,count(*) as nombre from evenements group by prix");


                     while(qq.next())
                     {series_1->append(qq.value(0).toString()+": "+qq.value(1).toString(),qq.value(1).toInt());}

                    QChart *chart_1 = new QChart();
                    chart_1->addSeries(series_1);
                    chart_1->setTitle("Statistiques des prix des evenements");
                    chart_1->setBackgroundBrush(Qt::transparent);
                    QChartView *chartview_1 = new QChartView(chart);
                    chartview_1->setRenderHint(QPainter::Antialiasing);
                    chartview_1->setParent(ui->horizontalFrame_4);
                    chartview_1->resize(400,300);

                    chart_1->setAnimationOptions(QChart::AllAnimations);
                    chart_1->legend()->setVisible(true);
                    chart_1->legend()->setAlignment(Qt::AlignRight);
                    series_1->setLabelsVisible(true);
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
    smtp->sendMail("Qt projet esprit", ui->comboBox_2->currentText() ,"Planning"," Planning du votre seance de travaille est : "+ui->DATE_PRESENCE_2->date().toString("dddd, dd MMMM yyyy"));
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
    ui->verticalLayout->removeWidget(chartView);

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
        click->play();
        Smtp* smtp = new Smtp("dedsec1450@gmail.com", "wassimben123", "smtp.gmail.com", 465);
        smtp->sendMail("Reservation", ui->subject_3->text(),ui->msg_3->toPlainText(),"test" );

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

//nouveautes
void MainWindow::on_pushButtonAjouter_4_clicked()
{
    ui->tabWidget1->setCurrentIndex(2);

}

void MainWindow::on_pushButtonAjouter_evenement_4_clicked()
{


    Evenement e(ui->lineEditId_4->text().toInt(),ui->lineEditNom_4->text(), ui->lineEditPrix_4->text().toFloat(),ui->dateEdit1_4->date().toString(),ui->textEditDescription_4->toPlainText());
    bool test = e.add_evenement();
    QFile file("C:/Users/dedpy/Desktop/Historique.txt");
            if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                return;

            QTextStream cout(&file);
    if (test)

    {
        ui->lineEditNom_4->setText("");
        ui->lineEditId_4->setText("");
    ui->lineEditPrix_4->setText("");
        ui->textEditDescription_4->setText("");

       QString message2="Vous avez ajouté un evenement\n";
            cout << message2;
            QFile file("C:/Users/dedpy/Desktop/Historique.txt");
           if (!file.open(QIODevice::ReadOnly))
           {
               QMessageBox::information(0,"info",file.errorString());
           }
           QTextStream in (&file);
          ui->textBrowser_4->setText(in.readAll());
        QMessageBox::information(nullptr,QObject::tr("Add Evenement"),QObject::tr("Evenement ajouté avec success\n click ok to exit"),QMessageBox::Ok);
        ui->tableView_7->setModel(evenementtmp.show_evenements());
    }
    else

    {

        QMessageBox::warning(nullptr,QObject::tr("Add Evenement"),QObject::tr("Evenement n a pas ete ajouté\n click ok to exit"),QMessageBox::Ok);

    }
}

void MainWindow::on_pushButtonSupprimer_4_clicked()
{
    int row=ui->tableView_7->selectionModel()->currentIndex().row();
    int id=ui->tableView_7->model()->index(row,0).data().toInt();
    bool  test = evenementtmp.delete_evenement(id);
    QFile file("C:/Users/dedpy/Desktop/Historique.txt");
            if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                return;

            QTextStream cout(&file);
    if (test)

    {



   QString message2="Vous avez supprimé un evenement\n";
        cout << message2;
        QFile file("C:/Users/dedpy/Desktop/Historique.txt");
       if (!file.open(QIODevice::ReadOnly))
       {
           QMessageBox::information(0,"info",file.errorString());
       }
       QTextStream in (&file);
      ui->textBrowser_4->setText(in.readAll());
        QMessageBox::information(nullptr,QObject::tr("delete Evenement"),QObject::tr("Evenement supprime avec success\n click ok to exit"),QMessageBox::Ok);
        ui->tableView_7->setModel(evenementtmp.show_evenements());
    }
    else

    {
        QMessageBox::warning(nullptr,QObject::tr("delete Evenement"),QObject::tr("Evenement n a pas ete supprime\n click ok to exit"),QMessageBox::Ok);

    }

}

void MainWindow::on_pushButtonAjouterOffre_4_clicked()
{
     ui->tabWidget1->setCurrentIndex(3);
}


void MainWindow::on_pushButtonAfficherOffre_4_clicked()
{
    ui->tabWidget1->setCurrentIndex(4);
}

void MainWindow::on_pushButtonAfficher_4_clicked()
{
     ui->tabWidget1->setCurrentIndex(1);
}


void MainWindow::on_pushButtonAjouter_Offre1_4_clicked()
{
    Offre o(ui->lineEditIdOffre_4->text().toInt(),ui->lineEditNomOffre_4->text(), ui->lineEditPrixOffre_4->text().toDouble(),ui->textEditDescriptionOffre_4->toPlainText());
    bool test = o.add_offre();
    QFile file("C:/Users/dedpy/Desktop/Historique.txt");
            if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                return;

            QTextStream cout(&file);
    if (test)

    {




QString message2="Vous avez ajouté un offre\n";
cout << message2;
QFile file("C:/Users/dedpy/Desktop/Historique.txt");
if (!file.open(QIODevice::ReadOnly))
{
   QMessageBox::information(0,"info",file.errorString());
}
QTextStream in (&file);
ui->textBrowser_4->setText(in.readAll());
        ui->lineEditNomOffre_4->setText("");
        ui->lineEditIdOffre_4->setText("");
    ui->lineEditPrixOffre_4->setText("");
        ui->textEditDescriptionOffre_4->setText("");
        QMessageBox::information(nullptr,QObject::tr("Add Offre"),QObject::tr("Offre ajouté avec success\n click ok to exit"),QMessageBox::Ok);
        ui->tableView_8->setModel(offretmp.show_offres());
    }
    else

    {
        QMessageBox::warning(nullptr,QObject::tr("Add Offre"),QObject::tr("Offre n a pas ete ajouté\n click ok to exit"),QMessageBox::Ok);

    }
}


void MainWindow::on_pushButtonRetour_menu_4_clicked()
{
     ui->tabWidget1->setCurrentIndex(0);
}

void MainWindow::on_pushButtonSupprimer_offre_4_clicked()
{
    int row=ui->tableView_8->selectionModel()->currentIndex().row();
    int id=ui->tableView_8->model()->index(row,0).data().toInt();
    bool  test = offretmp.delete_offre(id);
    QFile file("C:/Users/dedpy/Desktop/Historique.txt");
            if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                return;

            QTextStream cout(&file);
    if (test)

    {




QString message2="Vous avez supprimé un offre\n";
cout << message2;
QFile file("C:/Users/dedpy/Desktop/Historique.txt");
if (!file.open(QIODevice::ReadOnly))
{
QMessageBox::information(0,"info",file.errorString());
}
QTextStream in (&file);
ui->textBrowser_4->setText(in.readAll());
        QMessageBox::information(nullptr,QObject::tr("delete Offre"),QObject::tr("Offre supprime avec success\n click ok to exit"),QMessageBox::Ok);
        ui->tableView_8->setModel(offretmp.show_offres());
    }
    else

    {
        QMessageBox::warning(nullptr,QObject::tr("delete Offre"),QObject::tr("Offre n a pas ete supprime\n click ok to exit"),QMessageBox::Ok);

    }
}

void MainWindow::on_pushButtonRetour_17_clicked()
{
    ui->tabWidget1->setCurrentIndex(0);
}

void MainWindow::on_pushButtonRetour_18_clicked()
{
     ui->tabWidget1->setCurrentIndex(0);
}

void MainWindow::on_pushButtonRetour_16_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButtonAnnuler_4_clicked()
{
    Evenement e(ui->lineEditId_4->text().toInt(),ui->lineEditNom_4->text(), ui->lineEditPrix_4->text().toDouble(),ui->dateEdit1_4->date().toString(),ui->textEditDescription_4->toPlainText());
    bool test = e.update_evenement(ui->lineEditId_4->text().toInt());
    QFile file("C:/Users/dedpy/Desktop/Historique.txt");
            if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                return;

            QTextStream cout(&file);
    if (test)

    {

QString message2="Vous avez modifié un evenement\n";
    cout << message2;
    QFile file("C:/Users/dedpy/Desktop/Historique.txt");
   if (!file.open(QIODevice::ReadOnly))
   {
       QMessageBox::information(0,"info",file.errorString());
   }
   QTextStream in (&file);
  ui->textBrowser_4->setText(in.readAll());
        ui->lineEditNom_4->setText("");
        ui->lineEditId_4->setText("");
    ui->lineEditPrix_4->setText("");
        ui->textEditDescription_4->setText("");
        QMessageBox::information(nullptr,QObject::tr("Update Evenement"),QObject::tr("Evenement modifié avec success\n click ok to exit"),QMessageBox::Ok);
        ui->tableView_7->setModel(evenementtmp.show_evenements());
    }
    else
    {
        QMessageBox::warning(nullptr,QObject::tr("Update Evenement"),QObject::tr("Evenement n a pas ete modifié\n click ok to exit"),QMessageBox::Ok);

    }
}

void MainWindow::on_pushButton_9_clicked()
{
    int row=ui->tableView_7->selectionModel()->currentIndex().row();
    int id=ui->tableView_7->model()->index(row,0).data().toInt();
    QString id_str=QString::number(id);
    ui->lineEditId_4->setText(id_str);
    ui->tabWidget1->setCurrentIndex(2);

}

void MainWindow::on_pushButton_31_clicked()
{
    int row=ui->tableView_8->selectionModel()->currentIndex().row();
    int id=ui->tableView_8->model()->index(row,0).data().toInt();
    QString id_str=QString::number(id);
    ui->lineEditIdOffre_4->setText(id_str);
    ui->tabWidget1->setCurrentIndex(3);

}

void MainWindow::on_pushButton_10_clicked()
{
     ui->tableView_7->setModel(evenementtmp.tri_evenements(ui->comboBox_2->currentText()));
}

void MainWindow::on_pushButton_11_clicked()
{
     ui->tableView_7->setModel(evenementtmp.find_evenements(ui->comboBox_9->currentText(),ui->lineEditRech_4->text()));
}

void MainWindow::on_pushButton_29_clicked()
{
    ui->tableView_7->setModel(evenementtmp.show_evenements());
}

void MainWindow::on_pushButton_33_clicked()
{
    Smtp* smtp = new Smtp("dedsec1450@gmail.com", "wassimben123", "smtp.gmail.com", 465);
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
        smtp->sendMail("bacim.oueslati@esprit.tn",ui->lineEdit_4->text(),ui->lineEdit_9->text(),ui->plainTextEdit_2->toPlainText());

}

void MainWindow::on_pushButton_30_clicked()
{
    QString strStream;
                       QTextStream out(&strStream);

                        const int rowCount = ui->tableView_7->model()->rowCount();
                        const int columnCount = ui->tableView_7->model()->columnCount();
                       out <<  "<html>\n"
                       "<head>\n"
                                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                        <<  QString("<title>%1</title>\n").arg("strTitle")
                                        <<  "</head>\n"
                                        "<body bgcolor=#ffffff link=#5000A0>\n"

                                       //     "<align='right'> " << datefich << "</align>"
                                        "<center> <H1>Liste des evenements</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                    // headers
                                    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                    out<<"<cellspacing=10 cellpadding=3>";
                                    for (int column = 0; column < columnCount; column++)
                                        if (!ui->tableView_7->isColumnHidden(column))
                                            out << QString("<th>%1</th>").arg(ui->tableView_7->model()->headerData(column, Qt::Horizontal).toString());
                                    out << "</tr></thead>\n";

                                    // data table
                                    for (int row = 0; row < rowCount; row++) {
                                        out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                        for (int column = 0; column < columnCount; column++) {
                                            if (!ui->tableView_7->isColumnHidden(column)) {
                                                QString data = ui->tableView_7->model()->data(ui->tableView_7->model()->index(row, column)).toString().simplified();
                                                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                            }
                                        }
                                        out << "</tr>\n";
                                    }
                                    out <<  "</table> </center>\n"
                                        "</body>\n"
                                        "</html>\n";

                              QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                                if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                               QPrinter printer (QPrinter::PrinterResolution);
                                printer.setOutputFormat(QPrinter::PdfFormat);
                               printer.setPaperSize(QPrinter::A4);
                              printer.setOutputFileName(fileName);

                               QTextDocument doc;
                                doc.setHtml(strStream);
                                doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                                doc.print(&printer);
}

void MainWindow::on_pushButton_32_clicked()
{
    QTableView *table;
           table = ui->tableView_8;

           QString filters("CSV files (.csv);;All files (.*)");
           QString defaultFilter("CSV files (*.csv)");
           QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                              filters, &defaultFilter);
           QFile file(fileName);

           QAbstractItemModel *model =  table->model();
           if (file.open(QFile::WriteOnly | QFile::Truncate)) {
               QTextStream data(&file);
               QStringList strList;
               for (int i = 0; i < model->columnCount(); i++) {
                   if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                       strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                   else
                       strList.append("");
               }
               data << strList.join(";") << "\n";
               for (int i = 0; i < model->rowCount(); i++) {
                   strList.clear();
                   for (int j = 0; j < model->columnCount(); j++) {

                       if (model->data(model->index(i, j)).toString().length() > 0)
                           strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                       else
                           strList.append("");
                   }
                   data << strList.join(";") + "\n";
               }
               file.close();
               QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
           }
}

void MainWindow::on_pushButtonRetour_4_clicked()
{

}

void MainWindow::on_pushButton_35_clicked()
{
    QFile file("C:/Users/dedpy/Desktop/notes.txt");
            if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                return;
            QTextStream cout(&file);
QString message2="- "+ui->plainTextEdit_5->toPlainText() +"\n" ;
    cout << message2;
    ui->plainTextEdit_5->setPlainText("");
    ui->pushButton_35->hide();
    ui->plainTextEdit_5->hide();
}

void MainWindow::on_pushButton_34_clicked()
{
    ui->pushButton_35->show();
    ui->plainTextEdit_5->show();
}

void MainWindow::on_pushButton_36_clicked()
{
    if (ui->comboBox_11->currentText()=="Dark mode")
     {
        ui->centralwidget->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:1, y1:0, x2:1, y2:1, stop:0 black,stop:1 rgba(56, 63, 77, 255));");
    }
    if (ui->comboBox_11->currentText()=="Light mode")
     {
        ui->centralwidget->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:1, y1:0, x2:1, y2:1, stop:0 #d5d0e5,stop:1 #f3e6e8);color:black;");

    }
    if (ui->comboBox_11->currentText()=="Normal mode")
     {
        ui->centralwidget->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:1, y1:0, x2:1, y2:1, stop:0 rgba(102, 115, 140, 255),stop:1 rgba(56, 63, 77, 255));QPushButton        {            background-color: qlineargradient(spread:repeat, x1:0.486, y1:0, x2:0.505, y2:1, stop:0.00480769 rgba(170, 0, 0, 255),stop:1 rgba(122, 0, 0, 255));            color: #ffffff;            font-weight: bold;            border-style: solid;            border-width: 1px;           border-radius: 3px;         border-color: #051a39;            padding: 5px;                }");

    }
}

void MainWindow::on_pushButton_gestionnouv_clicked()
{
    click->play();
    ui->stackedWidget->setCurrentIndex(4);
}



//khalil


void MainWindow::on_pushButton_ajouterproduit_clicked()
{
    ajouterproduit ajouter;
    ajouter.setModal(true);
    ajouter.exec();

    Connection1 conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db1);
    qry->prepare("select * from produit");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_produit->setModel(modal);
    mysystem1->showMessage(tr("notification"),tr("Ajout effectiué avec succés"));
    mysystem1->show();

}

void MainWindow::on_pushButton_modifierproduit_clicked()
{
    modifierproduit modifier;
    modifier.setModal(true);
    modifier.exec();

    Connection1 conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db1);
    qry->prepare("select * from produit");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_produit->setModel(modal);
    mysystem1->show();
    mysystem1->showMessage(tr("notification"),tr("Modification effectiué avec succés"));
}

void MainWindow::on_pushButton_supprimerproduit_clicked()
{
    supprimerproduit supp;
    supp.setModal(true);
    supp.exec();

    Connection1 conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db1);
    qry->prepare("select * from produit");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_produit->setModel(modal);
    mysystem1->show();
    mysystem1->showMessage(tr("notification"),tr("Suppression effectiué avec succés"));
}


void MainWindow::on_pushButton_chercherproduit_clicked()
{

            QString id_p= ui->lineEdit->text() ;
            ui->tableView_produit->setModel(tempproduit.recherche(id_p));


}



void MainWindow::on_pushButtonproduit_clicked()
{
      ui->tableView_produit->setModel(tempproduit.afficher());
      ui->tableView_produit->setModel(tempproduit.afficher());
            int akther;
                       int akal;
                       int somme;
                       QString akther50;
                       QString akal50;
                       QSqlQuery q1;

                       q1.prepare("SELECT COUNT(*) FROM produit where to_number(prix_p)>50");
                       q1.exec();
                       q1.first() ;
                       akther=(q1.value(0).toInt());

                       q1.prepare("SELECT COUNT(*) FROM produit where to_number(prix_p)<50");
                       q1.exec();
                       q1.first() ;
                       akal=(q1.value(0).toInt());

                       q1.prepare("SELECT COUNT(*) FROM produit ");
                       q1.exec();
                       q1.first() ;
                       somme=(q1.value(0).toInt());

                       akther=((double)akther/(double)somme)*100;
                       akal=((double)akal/(double)somme)*100;

                       akther50= QString::number(akther);
                       akal50=QString::number(akal);
                       QPieSeries *series1;
                        series1= new  QPieSeries();
                        series1->append(" plus ce que 50 DT "+akther50+"%",akther);
                        series1->append(" moins 50 DT  "+akal50+"%",akal);
                        QPieSlice *slice00 = series1->slices().at(0);
                         slice00->setLabelVisible();

                         QPieSlice *slice01 = series1->slices().at(1);
                            slice01->setExploded();
                            slice01->setLabelVisible();
                            slice01->setPen(QPen(Qt::green, 3));
                            slice01->setBrush(Qt::darkYellow);

                             QChart *chart1 = new QChart();
                             chart1->addSeries(series1);
                             chart1->setTitle("Statistique des types  ");
                             chart1->legend()->show();
                             QChartView *chartView1 = new QChartView(chart1);
                             chartView1->setRenderHint(QPainter::Antialiasing);
                             ui->vertical_layout_stat1->addWidget(chartView1);
                        show();
                        ui->vertical_layout_stat1->removeWidget(chartView1);
}

void MainWindow::on_radioButton_pripr_clicked()
{
    Connection1 conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db1);
    qry->prepare("select * from produit ORDER BY prix_p");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_produit->setModel(modal);
}

void MainWindow::on_radioButton_typepr_clicked()
{
    Connection1 conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db1);
    qry->prepare("select * from produit ORDER BY type_p");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_produit->setModel(modal);
}

void MainWindow::on_radioButton_quantitepr_clicked()
{
    Connection1 conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db1);
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

    Connection1 conn;
    QSqlQueryModel * modal1 = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db1);
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

    Connection1 conn;
    QSqlQueryModel * modal1 = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db1);
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

    Connection1 conn;
    QSqlQueryModel * modal1 = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db1);
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








void MainWindow::on_pushButton_stat_clicked()
{
    QString type_p= ui->lineEdit->text() ;
    int s,n;
    s=tempproduit.stat(type_p);
    n=tempproduit.nbtotal();
    ui->tableView_produit->setModel(tempproduit.statfinal(type_p));
    //ui->label_stat->setNum((s*100)/n);
}

void MainWindow::on_pushButton_gestionstock_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_pushButton_mailCom_clicked()
{
    SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);
                       smtp.setUser("smartrestaurant28@gmail.com");
                       smtp.setPassword("behija12345678");
                       MimeMessage message;
                       message.setSender(new EmailAddress("smartrestaurant28@gmail.com", "Smart Restaurant"));
                       QString emaiil =ui->lineEdit_mailCom->text();
                       message.addRecipient(new EmailAddress(emaiil, ""));
                       message.setSubject("Information");
                       MimeText text;
                       QString emaill = ui->textEdit_mailtextCom->toPlainText();
                       text.setText(emaill);
                       message.addPart(&text);
                       smtp.connectToHost();
                       smtp.login();
                       if(smtp.sendMail(message))
                       {
                           QMessageBox::information(this, "PAS D'ERREUR", "Envoyé");
                       }
                       else
                       {
                           QMessageBox::critical(this, "ERREUR", "Non Envoyé (probleme de connexion)");
                       }
                       smtp.quit();
}


//yassin
void MainWindow::on_pushButton_clicked()
{
    QString id = ui->lineEdit_id->text();
    QString nom= ui->lineEdit_nom->text();
    QString prenom= ui->lineEdit_prenom->text();
    QString num= ui->lineEdit_num->text();
    QString mail= ui->lineEdit_mail->text();
    QString adress= ui->lineEdit_adress->text();

fclient c(id,nom,prenom,num,mail,adress);

if(id=="" || nom=="" || prenom=="" || num=="" || mail=="" || adress==""){
    QMessageBox::critical(nullptr, QObject::tr("ajouter client"),
                          QObject::tr("merci de remplir tout les champs."),QMessageBox::Cancel);
}


    bool test=c.ajouter();
    if(test)
    {
         ui->lineEdit_id->clear();
         ui->lineEdit_nom->clear();
         ui->lineEdit_prenom->clear();
         ui->lineEdit_num->clear();
         ui->lineEdit_mail->clear();
         ui->lineEdit_adress->clear();


        ui->tableView->setModel(tmpclient.afficher());//refresh
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
        notifyIcon->show();
        notifyIcon->setIcon(QIcon("icone.png"));


        notifyIcon->showMessage("GESTION CLIENT  CLIENTS ","client Ajouté",QSystemTrayIcon::Information,15000);

    QMessageBox::information(nullptr, QObject::tr("ajouter client"),
                          QObject::tr("client ajouté./n"
                             "click cancel to exit."),QMessageBox::Cancel);
    }

    else
        QMessageBox::critical(nullptr, QObject::tr("ajouter client"),
                              QObject::tr("Erreur !./n"
                                 "click cancel to exit."),QMessageBox::Cancel);


}



void MainWindow::on_tableView_activated(const QModelIndex &index)
{

    QString val=ui->tableView->model()->data(index).toString();
       QSqlQuery qry;
       qry.prepare("select * from CLIENT where ID='"+val+"'");
       if(qry.exec())
       {
           while(qry.next())
           {
               ui->lineEdit_ids->setText(qry.value(0).toString());
               ui->lineEdit_id->setText(qry.value(0).toString());
               ui->lineEdit_nom->setText(qry.value(1).toString());
               ui->lineEdit_prenom->setText(qry.value(2).toString());
               ui->lineEdit_num->setText(qry.value(3).toString());
               ui->lineEdit_mail->setText(qry.value(4).toString());
               ui->lineEdit_adress->setText(qry.value(5).toString());





           }

       }
       else
       {
           QMessageBox::critical(this,tr("error::"),qry.lastError().text());
       }
}

void MainWindow::on_pushButton_3_clicked()
{
    QString id = ui->lineEdit_ids->text();
    if(id=="" ){
        QMessageBox::critical(nullptr, QObject::tr("supprimer client"),
                              QObject::tr("merci de remplir tout les champs."),QMessageBox::Cancel);
    }

    bool test=tmpclient.supprimer(id);
    if(test)
    {ui->tableView->setModel(tmpclient.afficher());//refresh

        ui->lineEdit_ids->clear();


        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
        notifyIcon->show();
        notifyIcon->setIcon(QIcon("icone.png"));


        notifyIcon->showMessage("GESTION  CLIENTS ","Client supprimé",QSystemTrayIcon::Information,15000);

        QMessageBox::information(nullptr, QObject::tr("Supprimer client"),
                    QObject::tr("client supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un client"),
                    QObject::tr("Erreur !.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_4_clicked()
{
    QString id = ui->lineEdit_id->text();
    QString nom= ui->lineEdit_nom->text();
    QString prenom= ui->lineEdit_prenom->text();
    QString num= ui->lineEdit_num->text();
    QString mail= ui->lineEdit_mail->text();
    QString adress= ui->lineEdit_adress->text();
    if(id=="" || nom=="" || prenom=="" || num=="" || mail=="" || adress==""){
        QMessageBox::critical(nullptr, QObject::tr("modifier client"),
                              QObject::tr("merci de remplir tout les champs."),QMessageBox::Cancel);
    }


    QSqlQuery query;
    query.prepare("UPDATE CLIENT SET ID='"+id+"',NOM='"+nom+"',PRENOM='"+prenom+"',NUM='"+num+"',MAIL='"+mail+"',ADRESS='"+adress+"' where ID = '"+id+"'");
    bool test = query.exec();
    if(test)
    {

       ui->tableView->setModel(tmpclient.afficher());
       ui->lineEdit_id->clear();
       ui->lineEdit_nom->clear();
       ui->lineEdit_prenom->clear();
       ui->lineEdit_num->clear();
       ui->lineEdit_mail->clear();
       ui->lineEdit_adress->clear();


       QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
       notifyIcon->show();
       notifyIcon->setIcon(QIcon("icone.png"));



       notifyIcon->showMessage("GESTION   CLIENTS ","Client Modifié",QSystemTrayIcon::Information,15000);




        QMessageBox::information(nullptr, QObject::tr("Modifier Client"),
                    QObject::tr("Client Modifieé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Modifier Client"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->tableView->setModel(tmpclient.afficher());
    ui->lineEdit_id->clear();
    ui->lineEdit_nom->clear();
    ui->lineEdit_prenom->clear();
    ui->lineEdit_num->clear();
    ui->lineEdit_mail->clear();
    ui->lineEdit_adress->clear();
}

void MainWindow::on_pushButton_6_clicked()
{
    QString id = ui->lineEdit_id_2->text();
    QString date= ui->lineEdit_date->text();
    QString lieu= ui->lineEdit_lieu->text();

    QString etat=ui->comboBox->currentText();
flivraison l(id,date,lieu,etat);
if(id=="" || date=="" || lieu=="" || etat=="" ){
    QMessageBox::critical(nullptr, QObject::tr("ajouter livraison"),
                          QObject::tr("merci de remplir tout les champs."),QMessageBox::Cancel);
}




    bool test=l.ajouter();
    if(test)
    {
         ui->lineEdit_id_2->clear();
         ui->lineEdit_date->clear();
         ui->lineEdit_lieu->clear();




        ui->tableView_2->setModel(tmplivraison.afficher());//refresh
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
        notifyIcon->show();
        notifyIcon->setIcon(QIcon("icone.png"));

        notifyIcon->showMessage("GESTION CLIENT  CLIENTS ","livraison Ajouté",QSystemTrayIcon::Information,15000);

    QMessageBox::information(nullptr, QObject::tr("ajouter livraison"),
                          QObject::tr("livraison ajouté./n"
                             "click cancel to exit."),QMessageBox::Cancel);
    }

    else
        QMessageBox::critical(nullptr, QObject::tr("ajouter livraison"),
                              QObject::tr("Erreur !./n"
                                 "click cancel to exit."),QMessageBox::Cancel);


}



void MainWindow::on_pushButton_7_clicked()
{
    QString id = ui->lineEdit_5->text();
    bool test=tmplivraison.supprimer(id);
    if(id=="" ){
        QMessageBox::critical(nullptr, QObject::tr("ajouter livraison"),
                              QObject::tr("merci de remplir tout les champs."),QMessageBox::Cancel);
    }
    if(test)
    {ui->tableView_2->setModel(tmplivraison.afficher());//refresh
        ui->lineEdit_5->clear();
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
        notifyIcon->show();
        notifyIcon->setIcon(QIcon("icone.png"));

        notifyIcon->showMessage("GESTION   CLIENTS ","livraison supprimé",QSystemTrayIcon::Information,15000);

        QMessageBox::information(nullptr, QObject::tr("Supprimer une livraison"),
                    QObject::tr("livraison supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer une livraison"),
                    QObject::tr("Erreur !.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_8_clicked(){
    QString id = ui->lineEdit_id_2->text();
    QString date= ui->lineEdit_date->text();
    QString lieu= ui->lineEdit_lieu->text();
    QString etat=ui->comboBox->currentText();
    if(id=="" || date=="" || lieu=="" || etat=="" ){
        QMessageBox::critical(nullptr, QObject::tr("modifier livraison"),
                              QObject::tr("merci de remplir tout les champs."),QMessageBox::Cancel);
    }




QSqlQuery query;
query.prepare("UPDATE LIVRAISON SET ID='"+id+"',DATEE='"+date+"',LIEU='"+lieu+"',ETAT='"+etat+"' where ID = '"+id+"'");
bool test = query.exec();
if(test)
{

   ui->tableView_2->setModel(tmplivraison.afficher());
   ui->lineEdit_id_2->clear();
   ui->lineEdit_date->clear();
   ui->lineEdit_lieu->clear();

   QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
   notifyIcon->show();
   notifyIcon->setIcon(QIcon("icone.png"));

   notifyIcon->showMessage("GESTION CLIENT  CLIENTS ","Client Modifié",QSystemTrayIcon::Information,15000);

    QMessageBox::information(nullptr, QObject::tr("Modifier Client"),
                QObject::tr("Client Modifieé.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);



}
else
{
    QMessageBox::critical(nullptr, QObject::tr("Modifier Client"),
                QObject::tr("Erreur !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
}


void MainWindow::on_pushButton_14_clicked()
{
    //QDateTime datecreation = date.currentDateTime();
            //QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;
                   QPdfWriter pdf("C:/Users/dedpy/Desktop/livraison.pdf");
                   QPainter painter(&pdf);
                  int i = 4000;
                       painter.setPen(Qt::blue);
                       painter.setFont(QFont("Arial", 30));
                       painter.drawText(1100,1200,"Liste Des Livraison");
                       painter.setPen(Qt::black);
                       painter.setFont(QFont("Arial", 15));
                      // painter.drawText(1100,2000,afficheDC);
                       painter.drawRect(100,100,7300,2600);
                       //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
                       painter.drawRect(0,3000,9600,500);
                       painter.setFont(QFont("Arial", 9));
                       painter.drawText(200,3300,"ID");
                       painter.drawText(1300,3300,"DATE");
                       painter.drawText(2100,3300,"LIEU");
                       painter.drawText(3200,3300,"ETAT");

                       QSqlQuery query;
                       query.prepare("select * from LIVRAISON");
                       query.exec();
                       while (query.next())
                       {
                           painter.drawText(200,i,query.value(0).toString());
                           painter.drawText(1300,i,query.value(1).toString());
                           painter.drawText(2200,i,query.value(2).toString());
                           painter.drawText(3200,i,query.value(3).toString());

                          i = i + 500;
                       }
                       int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                           if (reponse == QMessageBox::Yes)
                           {
                               QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                               notifyIcon->show();
                               notifyIcon->setIcon(QIcon("icone.png"));

                               notifyIcon->showMessage("GESTION  CLIENTS ","Liste LIVRAISON prete à imprimer",QSystemTrayIcon::Information,15000);

                               painter.end();
                           }
                           if (reponse == QMessageBox::No)
                           {
                                painter.end();
                           }
}

void MainWindow::on_tableView_2_activated(const QModelIndex &index)
{

    QString val=ui->tableView_2->model()->data(index).toString();
       QSqlQuery qry;
       qry.prepare("select * from LIVRAISON where ID='"+val+"'");
       if(qry.exec())
       {
           while(qry.next())
           {
               ui->lineEdit_5->setText(qry.value(0).toString());
               ui->lineEdit_id_2->setText(qry.value(0).toString());
               ui->lineEdit_date->setText(qry.value(1).toString());
               ui->lineEdit_lieu->setText(qry.value(2).toString());
               ui->comboBox->setCurrentText(qry.value(3).toString());








           }

       }
       else
       {
           QMessageBox::critical(this,tr("error::"),qry.lastError().text());
       }
}

void MainWindow::on_pushButton_17_clicked()
{
    ui->tableView_2->setModel(tmplivraison.afficher());
    ui->lineEdit_id_2->clear();
    ui->lineEdit_date->clear();
    ui->lineEdit_lieu->clear();

}

void MainWindow::on_pushButton_13_clicked()
{ QPdfWriter pdf("C:/Users/msi/OneDrive/Bureau/client.pdf");
    QPainter painter(&pdf);
   int i = 4000;
        painter.setPen(Qt::blue);
        painter.setFont(QFont("Arial", 30));
        painter.drawText(1100,1200,"Liste Des Livraison");
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 15));
       // painter.drawText(1100,2000,afficheDC);
        painter.drawRect(100,100,7300,2600);
        //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
        painter.drawRect(0,3000,9600,500);
        painter.setFont(QFont("Arial", 9));
        painter.drawText(200,3300,"ID");
        painter.drawText(1300,3300,"NOM");
        painter.drawText(2100,3300,"PRENOM");
        painter.drawText(3200,3300,"NUM");
        painter.drawText(4300,3300,"MAIL");
        painter.drawText(5400,3300,"ADRESS");


        QSqlQuery query;
        query.prepare("select * from CLIENT");
        query.exec();
        while (query.next())
        {
            painter.drawText(200,i,query.value(0).toString());
            painter.drawText(1300,i,query.value(1).toString());
            painter.drawText(2200,i,query.value(2).toString());
            painter.drawText(3200,i,query.value(3).toString());
            painter.drawText(4300,i,query.value(4).toString());
            painter.drawText(5400,i,query.value(5).toString());






           i = i + 500;
        }
        int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
            if (reponse == QMessageBox::Yes)
            {
                QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                notifyIcon->show();
                notifyIcon->setIcon(QIcon("icone.png"));

                notifyIcon->showMessage("GESTION  CLIENTS ","Liste CLIENTS prete à imprimer",QSystemTrayIcon::Information,15000);

                painter.end();
            }
            if (reponse == QMessageBox::No)
            {
                 painter.end();
            }
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
            QSqlQuery   *query= new QSqlQuery();
    if(ui->comboBox_4->currentText()=="ID"){
        query->prepare("SELECT * FROM CLIENT WHERE ID LIKE'"+arg1+"%'");//+tri
query->exec();
    model->setQuery(*query);
ui->tableView->setModel(model);


    }
    else {
        if(ui->comboBox_4->currentText()=="NOM"){
            query->prepare("SELECT * FROM CLIENT WHERE NOM LIKE'"+arg1+"%'");//+tri
    query->exec();
        model->setQuery(*query);
    ui->tableView->setModel(model);
        }
        else {
            if(ui->comboBox_4->currentText()=="PRENOM"){
            query->prepare("SELECT * FROM CLIENT WHERE PRENOM LIKE'"+arg1+"%'");//+tri
    query->exec();
        model->setQuery(*query);
    ui->tableView->setModel(model);
            }

        }

    }
}

void MainWindow::on_pushButton_12_clicked()
{
    QSqlQueryModel *model= new QSqlQueryModel();
            QSqlQuery   *query= new QSqlQuery();
    if(ui->comboBox_3->currentText()=="ID"){
        query->prepare("SELECT * FROM CLIENT order by ID");//+tri
query->exec();
    model->setQuery(*query);
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->setIcon(QIcon("icone.png"));

    notifyIcon->showMessage("GESTION CLIENT  CLIENTS ","Client trié",QSystemTrayIcon::Information,15000);
ui->tableView->setModel(model);




    }
    else {
        if(ui->comboBox_3->currentText()=="NOM"){
            query->prepare("SELECT * FROM CLIENT order by NOM");//+tri
    query->exec();
        model->setQuery(*query);
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
        notifyIcon->show();
        notifyIcon->setIcon(QIcon("icone.png"));

        notifyIcon->showMessage("GESTION CLIENT  CLIENTS ","Client trié",QSystemTrayIcon::Information,15000);
    ui->tableView->setModel(model);
        }


    }
}

void MainWindow::on_pushButton_16_clicked()
{
    QSqlQueryModel *model= new QSqlQueryModel();
            QSqlQuery   *query= new QSqlQuery();
           QString arg1=ui->comboBox_5->currentText();
    if(ui->comboBox_5->currentText()=="LIVRE"){
        query->prepare("SELECT * FROM LIVRAISON WHERE ETAT LIKE'"+arg1+"%'");//+tri
query->exec();
    model->setQuery(*query);
ui->tableView_2->setModel(model);


    }
    else {
        if(ui->comboBox_5->currentText()=="NON LIVRE"){
            query->prepare("SELECT * FROM LIVRAISON WHERE ETAT LIKE'"+arg1+"%'");//+tri
    query->exec();
        model->setQuery(*query);
    ui->tableView_2->setModel(model);
        }
}
}

void MainWindow::on_pushButton_15_clicked()
{
    QSqlQueryModel *model= new QSqlQueryModel();
            QSqlQuery   *query= new QSqlQuery();

        query->prepare("SELECT * FROM LIVRAISON order by ID");//+tri
query->exec();
    model->setQuery(*query);
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->setIcon(QIcon("icone.png"));

    notifyIcon->showMessage("GESTION LIVRAISON ","table trié",QSystemTrayIcon::Information,15000);
ui->tableView_2->setModel(model);

}

void MainWindow::on_pushButton_gestionclient_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_pushButton_retour_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_retour_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_19_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_retour_5_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(0);
}

void MainWindow::on_pushButton_20_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Deconnexion","Ets Vous sur ?", QMessageBox::Yes | QMessageBox::No);
       if(reply == QMessageBox::Yes){
           hide();
           MainWindow0* a = new class MainWindow0(this);
           a->show();
       }
}
