#include "supprimer_fournisseur.h"
#include "ui_supprimer_fournisseur.h"
#include "fournisseur.h"
#include <qmessagebox.h>

supprimer_fournisseur::supprimer_fournisseur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::supprimer_fournisseur)
{
    ui->setupUi(this);
}

supprimer_fournisseur::~supprimer_fournisseur()
{
    delete ui;
}

void supprimer_fournisseur::on_buttonBox_accepted()
{
    QString id_f = ui->lineEdit_id_f->text();
    Fournisseur temp;
    bool test=temp.supprimer_2(id_f);
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
