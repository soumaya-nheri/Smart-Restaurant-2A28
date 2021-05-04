#include "mainwindow0.h"
#include "ui_mainwindow0.h"
#include "QMessageBox"
#include "signup.h"
MainWindow0::MainWindow0(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow0)
{
    ui->setupUi(this);
    ui->line_username->setPlaceholderText("Nom D'utilisateur");
    ui->line_password->setPlaceholderText("Mot de Passe");
}

MainWindow0::~MainWindow0()
{
    delete ui;
}

void MainWindow0::on_pushButton_clicked()
{
    QString username,password;
        username=ui->line_username->text();
        password=ui->line_password->text();

        QSqlQuery qry;
        if(qry.exec("select * from CONNEXIONU where USERN= '"+username +"' and MDP= '"+password+"'"))
        {
            int count=0;
            while(qry.next())
            {
                count++;
            }
            if (count==1)
            {   QMessageBox::information(nullptr, QObject::tr("Connected"),
                                     QObject::tr("Connexion réussite\n""Click Cancel to exit")
                                     ,QMessageBox::Cancel);
                hide();
                home = new class MainWindow(this);
                home->show();


            }
            if (count>1)
                QMessageBox::warning(nullptr, QObject::tr("Duplicated"),
                             QObject::tr("Duplication\n""Click Cancel to exit")
                             ,QMessageBox::Cancel);
            if (count<1)
                QMessageBox::warning(nullptr, QObject::tr("Erreur"),
                             QObject::tr("Nom d'utilisateur ou mot de passe incorrecte\n""Click Cancel to exit")
                             ,QMessageBox::Cancel);
        }
            }







void MainWindow0::on_pushButton_creation1_clicked()
{
    ui->stackedWidget_connexion->setCurrentIndex(1);

}

void MainWindow0::on_pushButton_creationcompte_clicked()
{
    QString usern=ui->lineEdit_usercre->text();
        QString mdp=ui->lineEdit_mdpcre->text();

        signup A(usern,mdp);
        bool test=A.ajouter();
                    if(usern.isEmpty()){QMessageBox::warning(nullptr, QObject::tr("Nom et prénom"),
                                                                     QObject::tr("Veuillez indiquer votre nom et prénom\n""Click Cancel to exit")
                                                                     ,QMessageBox::Cancel);}
                   /* else if(username.isEmpty()){QMessageBox::warning(nullptr, QObject::tr("Nom d'utilisateur"),
                                                                     QObject::tr("Veuillez indiquer votre nom d'utilisateur\n""Click Cancel to exit")
                                                                     ,QMessageBox::Cancel);}*/
                    else if(mdp.isEmpty()){QMessageBox::warning(nullptr, QObject::tr("Mot de passe"),
                                                                     QObject::tr("Veuillez indiquer votre mot de passe\n""Click Cancel to exit")
                                                                     ,QMessageBox::Cancel);}
                    else if (test){
                                    QMessageBox::information(nullptr, QObject::tr("OK"),
                                                             QObject::tr("Compte creer\n""Click Cancel to exit")
                                                             ,QMessageBox::Cancel);
                                    ui->stackedWidget_connexion->setCurrentIndex(0);


                    }
                    else{
                                    QMessageBox::warning(nullptr, QObject::tr("OK"),
                                                 QObject::tr("Nom d'utilisateur existe déjà\n""Click Cancel to exit")
                                                 ,QMessageBox::Cancel);}

}

void MainWindow0::on_pushButton_annulercnx_clicked()
{
    ui->stackedWidget_connexion->setCurrentIndex(0);

}
