#include "modifier_2.h"
#include "ui_modifier_2.h"
#include "tables.h"
#include <QMessageBox>

modifier_2::modifier_2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifier_2)
{
    ui->setupUi(this);
}

modifier_2::~modifier_2()
{
    delete ui;
}

void modifier_2::on_buttonBox_accepted()
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
    bool test = T.modifier_2(Etat,Numero);
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
