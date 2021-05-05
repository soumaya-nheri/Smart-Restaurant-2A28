#include "supprimerproduit.h"
#include "ui_supprimerproduit.h"
#include "produit.h"
supprimerproduit::supprimerproduit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::supprimerproduit)
{
    ui->setupUi(this);
}

supprimerproduit::~supprimerproduit()
{
    delete ui;
}

void supprimerproduit::on_buttonBox_accepted()
{

        QString id_p = ui->lineEdit_id_p->text();
        bool test=temp.supprimer(id_p);
        if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                                     QObject::tr("Suppression effectuer\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
        }else
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                     QObject::tr("Suppresion non effectuer\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);

 }

