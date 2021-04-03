#include "ajouter_2.h"
#include "ui_ajouter_2.h"
#include "tables.h"
#include <QMessageBox>

ajouter_2::ajouter_2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajouter_2)
{
    ui->setupUi(this);
}

ajouter_2::~ajouter_2()
{
    delete ui;
}

void ajouter_2::on_buttonBox_accepted()
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
    bool test = T.ajouter_2();
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
