#include "ajouterproduit.h"
#include "ui_ajouterproduit.h"
#include "produit.h"
#include <QMessageBox>

ajouterproduit::ajouterproduit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajouterproduit)
{
    ui->setupUi(this);
}

ajouterproduit::~ajouterproduit()
{
    delete ui;
}

void ajouterproduit::on_buttonBox_accepted()
{
    QString id_p = ui->lineEdit_id_p->text();
    QString type_p = ui->lineEdit_type_p->text();
    QString desc_p = ui->lineEdit_desc_p->text();
    QString quantite_p = ui->lineEdit_quantite_p->text();
    QString prix_p = ui->lineEdit_prix_p->text();


    Produit C(id_p,type_p,desc_p,quantite_p,prix_p);
    bool test = C.ajouter();
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


