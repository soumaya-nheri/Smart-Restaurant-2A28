#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db.CreateConnection();
    ui->tabWidget1->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonAjouter_clicked()
{
    ui->tabWidget1->setCurrentIndex(2);

}

void MainWindow::on_pushButtonAjouter_evenement_clicked()
{

    Evenement e(ui->lineEditId->text().toInt(),ui->lineEditNom->text(), ui->lineEditPrix->text().toDouble(),ui->dateEdit1->date().toString(),ui->textEditDescription->toPlainText());
    bool test = e.add_evenement();
    if (test)

    {
        QMessageBox::information(nullptr,QObject::tr("Add Evenement"),QObject::tr("Evenement ajouté avec success\n click ok to exit"),QMessageBox::Ok);
        ui->listViewEvenements->setModel(evenementtmp.show_evenements());
    }
    else

    {
        QMessageBox::warning(nullptr,QObject::tr("Add Evenement"),QObject::tr("Evenement n a pas ete ajouté\n click ok to exit"),QMessageBox::Ok);

    }
}

void MainWindow::on_pushButtonSupprimer_clicked()
{
    bool  test = evenementtmp.delete_evenement(ui->lineEdit_Id_a_supprimmer->text().toInt());
    if (test)

    {
        QMessageBox::information(nullptr,QObject::tr("delete Evenement"),QObject::tr("Evenement supprime avec success\n click ok to exit"),QMessageBox::Ok);
        ui->listViewEvenements->setModel(evenementtmp.show_evenements());
    }
    else

    {
        QMessageBox::warning(nullptr,QObject::tr("delete Evenement"),QObject::tr("Evenement n a pas ete supprime\n click ok to exit"),QMessageBox::Ok);

    }

}

void MainWindow::on_pushButtonAjouterOffre_clicked()
{
     ui->tabWidget1->setCurrentIndex(3);
}


void MainWindow::on_pushButtonAfficherOffre_clicked()
{
    ui->tabWidget1->setCurrentIndex(4);
}

void MainWindow::on_pushButtonAfficher_clicked()
{
     ui->tabWidget1->setCurrentIndex(1);
}


void MainWindow::on_pushButtonAjouter_Offre1_clicked()
{
    Offre o(ui->lineEditIdOffre->text().toInt(),ui->lineEditNomOffre->text(), ui->lineEditPrixOffre->text().toDouble(),ui->textEditDescriptionOffre->toPlainText());
    bool test = o.add_offre();
    if (test)

    {
        QMessageBox::information(nullptr,QObject::tr("Add Offre"),QObject::tr("Offre ajouté avec success\n click ok to exit"),QMessageBox::Ok);
        ui->listViewOffres->setModel(offretmp.show_offres());
    }
    else

    {
        QMessageBox::warning(nullptr,QObject::tr("Add Offre"),QObject::tr("Offre n a pas ete ajouté\n click ok to exit"),QMessageBox::Ok);

    }
}


void MainWindow::on_pushButtonRetour_menu_clicked()
{
     ui->tabWidget1->setCurrentIndex(0);
}

void MainWindow::on_pushButtonSupprimer_offre_clicked()
{

    bool  test = offretmp.delete_offre(ui->lineEdit_Id_Offre_a_supprimmer->text().toInt());
    if (test)

    {
        QMessageBox::information(nullptr,QObject::tr("delete Offre"),QObject::tr("Offre supprime avec success\n click ok to exit"),QMessageBox::Ok);
        ui->listViewOffres->setModel(offretmp.show_offres());
    }
    else

    {
        QMessageBox::warning(nullptr,QObject::tr("delete Offre"),QObject::tr("Offre n a pas ete supprime\n click ok to exit"),QMessageBox::Ok);

    }
}

void MainWindow::on_pushButtonRetour_2_clicked()
{
    ui->tabWidget1->setCurrentIndex(0);
}

void MainWindow::on_pushButtonRetour_5_clicked()
{
     ui->tabWidget1->setCurrentIndex(0);
}

void MainWindow::on_pushButtonRetour_4_clicked()
{
    ui->tabWidget1->setCurrentIndex(0);
}
