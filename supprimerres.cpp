#include "supprimerres.h"
#include "ui_supprimerres.h"
#include <qmessagebox.h>
#include "client.h"
supprimerres::supprimerres(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::supprimerres)
{
    ui->setupUi(this);
}

supprimerres::~supprimerres()
{
    delete ui;
}

void supprimerres::on_buttonBox_accepted()
{

        QString CIN = ui->lineEdit_cin->text();
        bool test=temp.supprimerres(CIN);
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

