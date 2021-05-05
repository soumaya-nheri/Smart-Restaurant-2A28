#include "modifierproduit.h"
#include "ui_modifierproduit.h"
#include "produit.h"
#include <QMessageBox>

modifierproduit::modifierproduit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifierproduit)
{
    ui->setupUi(this);
}

modifierproduit::~modifierproduit()
{
    delete ui;
}

void modifierproduit::on_buttonBox_accepted()
{
    QString id_p = ui->lineEdit_id_p->text();
    QString type_p = ui->lineEdit_type_p->text();
    QString desc_p = ui->lineEdit_desc_p->text();
    QString quantite_p = ui->lineEdit_quantite_p->text();
    QString prix_p = ui->lineEdit_prix_p->text();



     Produit P(id_p,type_p,desc_p,quantite_p,prix_p);
     bool test=P.modifier(id_p,type_p,desc_p,quantite_p,prix_p);
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("Modifier une reservationt !"),
                                 QObject::tr(" produit modifiée ! \n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else {

        QMessageBox::critical(nullptr, QObject::tr("Modifier Reservation"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
