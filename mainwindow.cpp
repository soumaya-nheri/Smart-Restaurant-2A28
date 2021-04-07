#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "conge.h"
#include <QPrinter>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    conge tmpconge;
    ui->setupUi(this);
    ui->tableView_staff->setModel(tmpstaff.afficher());
    QSqlQueryModel * modell = tmpconge.afficher();
    ui->tableViewConge->setModel( modell);
    ui->tableView_staff->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_staff->setSelectionMode(QAbstractItemView::SingleSelection);

    QSqlQueryModel *model2=new QSqlQueryModel();
    QString nom;
    model2->setQuery("select nom from staff");
    ui->comboBox_employe->setModel(model2);
    ui->comboBox->setModel(model2);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_staff_clicked()
{
    QString cin=ui->cin_staff->text();
    QString nom=ui->nom_staff->text();
    QString prenom=ui->prenom_staff->text();
    QString email=ui->email_staff->text();
    QString telephone=ui->tel_staff->text();
    QString login=ui->login_staff->text();
    QString password=ui->pass_staff->text();
    QString role=ui->role_staff->currentText();
    int salaire=ui->salaire_staff->text().toInt();

    staff staff(cin,nom,prenom,email,telephone,login,password,role,salaire);
    if (staff.ajouter())
    {
        ui->tableView_staff->setModel(tmpstaff.afficher());

    }
    else
    {
        qDebug() << "Erreur d'ajout.";
    }

}

void MainWindow::on_modifier_staff_clicked()
{
    if (ui->modifier_staff->isChecked())
    {

        ui->modifier_staff->setText(tr("Modifiable"));
        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("staff");
        tableModel->select();
        ui->tableView_staff->setModel(tableModel);
    }
    else
    {
        ui->modifier_staff->setText(tr("Modifier"));
        ui->tableView_staff->setModel(tmpstaff.afficher());

    }
}

void MainWindow::on_supprimer_staff_clicked()
{
    QItemSelectionModel *select = ui->tableView_staff->selectionModel();

    QString cin =select->selectedRows(0).value(0).data().toString();

    if(tmpstaff.supprimer(cin))
    {
        ui->tableView_staff->setModel(tmpstaff.afficher());

    }

}

void MainWindow::on_ajouter_clicked()
{
    conge tmpconge;
        if(ui->lineEditNumConge->text()!=""){
        QString id=ui->lineEditNumConge->text();
        /*QString nom=ui->lineEditType->text();*/
        QString nom=ui->comboBox_employe->currentText();
        QString dated=ui->dateEditDebut->date().toString();
        QString datef=ui->dateEditFin->date().toString();
        QString type=ui->comboBoxType->currentText();

        conge conge(id, nom, dated, datef, type);
        conge.ajouter();
        QSqlQueryModel * modell = tmpconge.afficher();
        ui->tableViewConge->setModel( modell);
        QSortFilterProxyModel *mm=new QSortFilterProxyModel(this);
           mm->setDynamicSortFilter(true);
           mm->setSourceModel(modell);
           ui->tableViewConge->setModel(mm);
           ui->tableViewConge->setSortingEnabled(true);
        foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
            widget->clear();
        }
    }
}


void MainWindow::on_pushButtonSuppr_clicked()
{
    conge tmpconge;


    QItemSelectionModel *select = ui->tableViewConge->selectionModel();
        QString idstaff =select->selectedRows(0).value(0).data().toString();
        if(tmpconge.supprimer(idstaff))
            {
               QSqlQueryModel * modell = tmpconge.afficher();
               ui->tableViewConge->setModel( modell);
               QSortFilterProxyModel *mm=new QSortFilterProxyModel(this);
               mm->setDynamicSortFilter(true);
               mm->setSourceModel(modell);
               ui->tableViewConge->setModel(mm);
               ui->tableViewConge->setSortingEnabled(true);
            }
}

void MainWindow::on_pushButtonEdit_clicked()
{
    if (ui->pushButtonEdit->isChecked())

                {

                    ui->pushButtonEdit->setDisabled(true);

                    ui->pushButtonEdit->setText("Modifiable");

                    QSqlTableModel *tableModel= new QSqlTableModel();

                    tableModel->setTable("CONGE");

                    tableModel->select();

                    ui->tableViewConge->setModel(tableModel);

                }

                else

                {

                    ui->pushButtonEdit->setText("Modifier");QSqlQueryModel * model = tmpstaff.afficher();

                    ui->tableView_staff->setModel( model);

                    QSortFilterProxyModel *m=new QSortFilterProxyModel(this);

                    m->setDynamicSortFilter(true);

                    m->setSourceModel(model);

                    ui->tableViewConge->setModel(m);

                    ui->tableViewConge->setSortingEnabled(true);

                }

    ui->pushButtonEdit->setChecked(false);
}

void MainWindow::on_pushButtonPDF_2_clicked()
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

void MainWindow::on_recherche_staff_textChanged(const QString &arg1)
{
    ui->tableView_staff->setModel(tmpstaff.recherchestaff(arg1));
}

void MainWindow::on_rechercher_staff_clicked()
{
    QString nom=ui->recherche_staff->text();
    QSqlQueryModel *verif_nom=tmpstaff.recherchestaff(nom);
    if (verif_nom!=nullptr)
    {
        ui->tableView_staff->setModel(verif_nom);
    }
}

void MainWindow::on_ajouter_planning_clicked()
{

}

void MainWindow::on_pushButtonRechercherConge_clicked()
{
    {

        conge e;

            QString text;

            if (ui->radioButton_ID->isChecked()==true)

        {

        text=ui->line_recherche_critere->text();

             if(text == "")


             {


                 ui->tableViewConge->setModel(e.afficher());


             }


             else


             {




                 ui->tableViewConge->setModel(e.chercher_emp(text));


             }

            }


             else if     (ui->radioButton_nom->isChecked()==true)

             {


                 text=ui->line_recherche_critere->text();

                      if(text == "")


                      {


                          ui->tableViewConge->setModel(e.afficher());



                      }


                      else


                      {




                          ui->tableViewConge->setModel(e.chercher_emp2(text));


                      }

             }
}
}
