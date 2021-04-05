#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include<QSqlError>
#include<QPainter>
#include<QPdfWriter>
#include<QtWidgets>
#include<fclient.h>
#include<flivraison.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(tmpclient.afficher());//refresh
    ui->tableView_2->setModel(tmplivraison.afficher());//refresh
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString id = ui->lineEdit_id->text();
    QString nom= ui->lineEdit_nom->text();
    QString prenom= ui->lineEdit_prenom->text();
    QString num= ui->lineEdit_num->text();
    QString mail= ui->lineEdit_mail->text();
    QString adress= ui->lineEdit_adress->text();

fclient c(id,nom,prenom,num,mail,adress);




    bool test=c.ajouter();
    if(test)
    {
         ui->lineEdit_id->clear();
         ui->lineEdit_nom->clear();
         ui->lineEdit_prenom->clear();
         ui->lineEdit_num->clear();
         ui->lineEdit_mail->clear();
         ui->lineEdit_adress->clear();


        ui->tableView->setModel(tmpclient.afficher());//refresh
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
        notifyIcon->show();
        notifyIcon->setIcon(QIcon("icone.png"));

        notifyIcon->showMessage("GESTION CLIENT  CLIENTS ","client Ajouté",QSystemTrayIcon::Information,15000);

    QMessageBox::information(nullptr, QObject::tr("ajouter client"),
                          QObject::tr("client ajouté./n"
                             "click cancel to exit."),QMessageBox::Cancel);
    }

    else
        QMessageBox::critical(nullptr, QObject::tr("ajouter client"),
                              QObject::tr("Erreur !./n"
                                 "click cancel to exit."),QMessageBox::Cancel);


}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{

    QString val=ui->tableView->model()->data(index).toString();
       QSqlQuery qry;
       qry.prepare("select * from CLIENT where ID='"+val+"'");
       if(qry.exec())
       {
           while(qry.next())
           {
               ui->lineEdit_ids->setText(qry.value(0).toString());
               ui->lineEdit_id->setText(qry.value(0).toString());
               ui->lineEdit_nom->setText(qry.value(1).toString());
               ui->lineEdit_prenom->setText(qry.value(2).toString());
               ui->lineEdit_num->setText(qry.value(3).toString());
               ui->lineEdit_mail->setText(qry.value(4).toString());
               ui->lineEdit_adress->setText(qry.value(5).toString());





           }

       }
       else
       {
           QMessageBox::critical(this,tr("error::"),qry.lastError().text());
       }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString id = ui->lineEdit_ids->text();
    bool test=tmpclient.supprimer(id);
    if(test)
    {ui->tableView->setModel(tmpclient.afficher());//refresh
        ui->lineEdit_ids->clear();
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
        notifyIcon->show();
        notifyIcon->setIcon(QIcon("icone.png"));

        notifyIcon->showMessage("GESTION  CLIENTS ","Client supprimé",QSystemTrayIcon::Information,15000);

        QMessageBox::information(nullptr, QObject::tr("Supprimer client"),
                    QObject::tr("client supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un client"),
                    QObject::tr("Erreur !.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString id = ui->lineEdit_id->text();
    QString nom= ui->lineEdit_nom->text();
    QString prenom= ui->lineEdit_prenom->text();
    QString num= ui->lineEdit_num->text();
    QString mail= ui->lineEdit_mail->text();
    QString adress= ui->lineEdit_adress->text();


    QSqlQuery query;
    query.prepare("UPDATE CLIENT SET ID='"+id+"',NOM='"+nom+"',PRENOM='"+prenom+"',NUM='"+num+"',MAIL='"+mail+"',ADRESS='"+adress+"' where ID = '"+id+"'");
    bool test = query.exec();
    if(test)
    {

       ui->tableView->setModel(tmpclient.afficher());
       ui->lineEdit_id->clear();
       ui->lineEdit_nom->clear();
       ui->lineEdit_prenom->clear();
       ui->lineEdit_num->clear();
       ui->lineEdit_mail->clear();
       ui->lineEdit_adress->clear();
       QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
       notifyIcon->show();
       notifyIcon->setIcon(QIcon("icone.png"));

       notifyIcon->showMessage("GESTION   CLIENTS ","Client Modifié",QSystemTrayIcon::Information,15000);

        QMessageBox::information(nullptr, QObject::tr("Modifier Client"),
                    QObject::tr("Client Modifieé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Modifier Client"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->tableView->setModel(tmpclient.afficher());
    ui->lineEdit_id->clear();
    ui->lineEdit_nom->clear();
    ui->lineEdit_prenom->clear();
    ui->lineEdit_num->clear();
    ui->lineEdit_mail->clear();
    ui->lineEdit_adress->clear();
}

void MainWindow::on_pushButton_5_clicked()
{
    QString id = ui->lineEdit_id_2->text();
    QString date= ui->lineEdit_date->text();
    QString lieu= ui->lineEdit_lieu->text();

    QString etat=ui->comboBox->currentText();
flivraison l(id,date,lieu,etat);




    bool test=l.ajouter();
    if(test)
    {
         ui->lineEdit_id_2->clear();
         ui->lineEdit_date->clear();
         ui->lineEdit_lieu->clear();




        ui->tableView_2->setModel(tmplivraison.afficher());//refresh
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
        notifyIcon->show();
        notifyIcon->setIcon(QIcon("icone.png"));

        notifyIcon->showMessage("GESTION CLIENT  CLIENTS ","livraison Ajouté",QSystemTrayIcon::Information,15000);

    QMessageBox::information(nullptr, QObject::tr("ajouter livraison"),
                          QObject::tr("livraison ajouté./n"
                             "click cancel to exit."),QMessageBox::Cancel);
    }

    else
        QMessageBox::critical(nullptr, QObject::tr("ajouter livraison"),
                              QObject::tr("Erreur !./n"
                                 "click cancel to exit."),QMessageBox::Cancel);


}




void MainWindow::on_pushButton_6_clicked()
{
    QString id = ui->lineEdit->text();
    bool test=tmplivraison.supprimer(id);
    if(test)
    {ui->tableView_2->setModel(tmplivraison.afficher());//refresh
        ui->lineEdit->clear();
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
        notifyIcon->show();
        notifyIcon->setIcon(QIcon("icone.png"));

        notifyIcon->showMessage("GESTION   CLIENTS ","livraison supprimé",QSystemTrayIcon::Information,15000);

        QMessageBox::information(nullptr, QObject::tr("Supprimer une livraison"),
                    QObject::tr("livraison supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer une livraison"),
                    QObject::tr("Erreur !.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_7_clicked(){
    QString id = ui->lineEdit_id_2->text();
    QString date= ui->lineEdit_date->text();
    QString lieu= ui->lineEdit_lieu->text();
    QString etat=ui->comboBox->currentText();




QSqlQuery query;
query.prepare("UPDATE LIVRAISON SET ID='"+id+"',DATEE='"+date+"',LIEU='"+lieu+"',ETAT='"+etat+"' where ID = '"+id+"'");
bool test = query.exec();
if(test)
{

   ui->tableView_2->setModel(tmplivraison.afficher());
   ui->lineEdit_id_2->clear();
   ui->lineEdit_date->clear();
   ui->lineEdit_lieu->clear();

   QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
   notifyIcon->show();
   notifyIcon->setIcon(QIcon("icone.png"));

   notifyIcon->showMessage("GESTION CLIENT  CLIENTS ","Client Modifié",QSystemTrayIcon::Information,15000);

    QMessageBox::information(nullptr, QObject::tr("Modifier Client"),
                QObject::tr("Client Modifieé.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);



}
else
{
    QMessageBox::critical(nullptr, QObject::tr("Modifier Client"),
                QObject::tr("Erreur !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
}


void MainWindow::on_pushButton_8_clicked()
{
    //QDateTime datecreation = date.currentDateTime();
            //QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;
                   QPdfWriter pdf("C:/Users/msi/OneDrive/Bureau/client.pdf");
                   QPainter painter(&pdf);
                  int i = 4000;
                       painter.setPen(Qt::blue);
                       painter.setFont(QFont("Arial", 30));
                       painter.drawText(1100,1200,"Liste Des Livraison");
                       painter.setPen(Qt::black);
                       painter.setFont(QFont("Arial", 15));
                      // painter.drawText(1100,2000,afficheDC);
                       painter.drawRect(100,100,7300,2600);
                       //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
                       painter.drawRect(0,3000,9600,500);
                       painter.setFont(QFont("Arial", 9));
                       painter.drawText(200,3300,"ID");
                       painter.drawText(1300,3300,"DATE");
                       painter.drawText(2100,3300,"LIEU");
                       painter.drawText(3200,3300,"ETAT");

                       QSqlQuery query;
                       query.prepare("select * from LIVRAISON");
                       query.exec();
                       while (query.next())
                       {
                           painter.drawText(200,i,query.value(0).toString());
                           painter.drawText(1300,i,query.value(1).toString());
                           painter.drawText(2200,i,query.value(2).toString());
                           painter.drawText(3200,i,query.value(3).toString());

                          i = i + 500;
                       }
                       int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                           if (reponse == QMessageBox::Yes)
                           {
                               QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                               notifyIcon->show();
                               notifyIcon->setIcon(QIcon("icone.png"));

                               notifyIcon->showMessage("GESTION  CLIENTS ","Liste LIVRAISON prete à imprimer",QSystemTrayIcon::Information,15000);

                               painter.end();
                           }
                           if (reponse == QMessageBox::No)
                           {
                                painter.end();
                           }
}
