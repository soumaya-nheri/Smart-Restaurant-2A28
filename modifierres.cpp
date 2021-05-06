#include "modifierres.h"
#include"ui_modifierres.h"
#include "client.h"
#include <QMessageBox>

modifierres::modifierres(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifierres)
{
    ui->setupUi(this);
}

modifierres::~modifierres()
{
    delete ui;
}


void modifierres::on_buttonBox_accepted()
{
    QString CIN = ui->lineEdit_cin->text();
    QString Nom = ui->lineEdit_nom->text();
    QString Prenom = ui->lineEdit_prenom->text();
    QString Mail = ui->lineEdit_mail->text();
    QString Tel = ui->lineEdit_tel->text();
    QDate Dat = ui->dateTimeEdit->date();


    Client C(CIN,Nom,Prenom,Mail,Tel,Dat);
     bool test=C.modifierres(CIN,Nom,Prenom,Mail,Tel,Dat);
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
