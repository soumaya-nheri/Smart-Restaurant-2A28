#include "modifier_fournisseur.h"
#include "ui_modifier_fournisseur.h"
#include "fournisseur.h"
#include <QMessageBox>

modifier_fournisseur::modifier_fournisseur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifier_fournisseur)
{
    ui->setupUi(this);
}

modifier_fournisseur::~modifier_fournisseur()
{
    delete ui;
}

void modifier_fournisseur::on_buttonBox_accepted()
{


    QString id_f=ui->lineEdit_id_f->text();
    QString nom_f=ui->lineEdit_nom_f->text();
    QString type_f=ui->lineEdit_type_f->text();
    QString num_f=ui->lineEdit_num_f->text();

    Fournisseur F(id_f,nom_f,type_f,num_f);
    bool test = F.modifier_2(id_f,nom_f,type_f,num_f);
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Modification effectuer\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

    }else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                 QObject::tr("Ajout non effectuer\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

}
