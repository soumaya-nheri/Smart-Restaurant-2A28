#include "supprimer_2.h"
#include "ui_supprimer_2.h"
#include "tables.h"
#include <qmessagebox.h>

supprimer_2::supprimer_2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::supprimer_2)
{
    ui->setupUi(this);
}

supprimer_2::~supprimer_2()
{
    delete ui;
}

void supprimer_2::on_buttonBox_accepted()
{
    QString Numero = ui->lineEdit_numero->text();
    Tables temp;
    bool test=temp.supprimer_2(Numero);
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
