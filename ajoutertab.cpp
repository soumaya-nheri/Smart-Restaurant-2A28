#include "ajoutertab.h"
#include "ui_ajoutertab.h"
#include "tables.h"
#include <QMessageBox>

ajoutertab::ajoutertab(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajoutertab)
{
    ui->setupUi(this);
}

ajoutertab::~ajoutertab()
{
    delete ui;
}

void ajoutertab::on_buttonBox_accepted()
{
    QString Etat;

    QString Numero = ui->lineEdit_numero->text();
    if (ui->radioButton->isChecked()){
         Etat="reserve";
    }
    else if (ui->radioButton_2->isChecked())
    {
        Etat="vide";
    }
    Tables T(Etat,Numero);
    bool test = T.ajoutertab();
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
