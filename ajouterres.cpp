#include "ajouterres.h"
#include "ui_ajouterres.h"
#include "client.h"
#include <QMessageBox>

ajouterres::ajouterres(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajouterres)
{
    ui->setupUi(this);
}

ajouterres::~ajouterres()
{
    delete ui;
}

void ajouterres::on_buttonBox_accepted()
{
    QString CIN = ui->lineEdit_cin->text();
    QString Nom = ui->lineEdit_nom->text();
    QString Prenom = ui->lineEdit_prenom->text();
    QString Mail = ui->lineEdit_mail->text();
    QString Tel = ui->lineEdit_tel->text();
    QDate Date = ui->dateTimeEdit->date();

    Client C(CIN,Nom,Prenom,Mail,Tel,Date);
    bool test = C.ajouterres();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectuer\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

    }else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                 QObject::tr("Ajout non effectuer\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
}
