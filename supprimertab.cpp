#include "supprimertab.h"
#include "ui_supprimertab.h"
#include "tables.h"
#include <qmessagebox.h>

supprimertab::supprimertab(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::supprimertab)
{
    ui->setupUi(this);
}

supprimertab::~supprimertab()
{
    delete ui;
}

void supprimertab::on_buttonBox_accepted()
{
    QString Numero = ui->lineEdit_numero->text();
    Tables temp;
    bool test=temp.supprimertab(Numero);
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
