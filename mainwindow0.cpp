#include "mainwindow0.h"
#include "ui_mainwindow0.h"
#include "QMessageBox"
#include <QTimer>
#include <QTime>
#include <QDateTime>
MainWindow0::MainWindow0(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow0)
{
    ui->setupUi(this);

    this->setWindowTitle("Connexion");
    ui->line_username->setPlaceholderText("Nom D'utilisateur");
    ui->line_password->setPlaceholderText("Mot de Passe");
    QTimer *timer_p=new QTimer(this);
           connect(timer_p, SIGNAL(timeout()), this,SLOT(showTime()));
           timer_p->start(1000);
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


void MainWindow0::showTime(){
    ui->timer->setText(QTime::currentTime().toString("hh:mm:ss"));

}

