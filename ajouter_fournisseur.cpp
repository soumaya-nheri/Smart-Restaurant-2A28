#include "ajouter_fournisseur.h"
#include "ui_ajouter_fournisseur.h"
#include "fournisseur.h"
#include <QMessageBox>

ajouter_fournisseur::ajouter_fournisseur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajouter_fournisseur)
{
    ui->setupUi(this);
}

ajouter_fournisseur::~ajouter_fournisseur()
{
    delete ui;
}

void ajouter_fournisseur::on_buttonBox_accepted()
{
   QString id_f=ui->lineEdit_id_f->text();
   QString nom_f=ui->lineEdit_nom_f->text();
   QString type_f=ui->lineEdit_type_f->text();
   QString num_f=ui->lineEdit_num_f->text();


    Fournisseur F(id_f,nom_f,type_f,num_f);
    bool test = F.ajouter_2();
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
