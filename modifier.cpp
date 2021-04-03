#include "modifier.h"
#include "ui_modifier.h"
#include "client.h"
#include <QMessageBox>

modifier::modifier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifier)
{
    ui->setupUi(this);
}

modifier::~modifier()
{
    delete ui;
}

void modifier::on_buttonBox_accepted()
{
    QString CIN = ui->lineEdit_cin->text();
    QString Nom = ui->lineEdit_nom->text();
    QString Prenom = ui->lineEdit_prenom->text();
    QString Mail = ui->lineEdit_mail->text();
    QString Tel = ui->lineEdit_tel->text();
    QDate Date = ui->dateTimeEdit->date();


    Client C(CIN,Nom,Prenom,Mail,Tel,Date);
     bool test=C.modifier(CIN,Nom,Prenom,Mail,Tel,Date);
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("Modifier une reservationt !"),
                                 QObject::tr(" reservation modifiée ! \n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else {

        QMessageBox::critical(nullptr, QObject::tr("Modifier Reservation"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
