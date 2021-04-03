#include "supprimer.h"
#include "ui_supprimer.h"

supprimer::supprimer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::supprimer)
{
    ui->setupUi(this);
}

supprimer::~supprimer()
{
    delete ui;
}

void supprimer::on_buttonBox_accepted()
{

        QString CIN = ui->lineEdit_cin->text();
        bool test=temp.supprimer(CIN);
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

