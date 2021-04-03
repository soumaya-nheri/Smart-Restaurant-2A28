#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "ajouter.h"
#include "modifier.h"
#include "supprimer.h"
#include "tables.h"
#include "ajouter_2.h"
#include "modifier_2.h"
#include "supprimer_2.h"
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include "smtp.h"
#include <QDebug>



Connection::Connection(){}

bool Connection::createconnection()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projet_2a");//inserer le nom de la source de données ODBC
    db.setUserName("system");//inserer nom de l'utilisateur
    db.setPassword("12345678");//inserer mot de passe de cet utilisateur

    if (db.open())
    test=true;
    return  test;
}

void Connection::closeconnection(){db.close();}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// MAILING


void MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file_2->setText( fileListString );

}


void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname_2->text(), ui->paswd_2->text(), ui->server_2->text(), ui->port_2->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(ui->uname_2->text(), ui->rcpt_2->text() , ui->subject_2->text(),ui->msg_2->toPlainText(), files );
    else
        smtp->sendMail(ui->uname_2->text(), ui->rcpt_2->text() , ui->subject_2->text(),ui->msg_2->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}


//~Mailing

void MainWindow::on_pushButton_ajouter_clicked()
{
    ajouter ajouter;
    ajouter.setModal(true);
    ajouter.exec();

    Connection conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db);
    qry->prepare("select * from reservation");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);

}

void MainWindow::on_pushButton_modifier_clicked()
{
    modifier modifier;
    modifier.setModal(true);
    modifier.exec();

    Connection conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db);
    qry->prepare("select * from reservation");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    supprimer supp;
    supp.setModal(true);
    supp.exec();

    Connection conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db);
    qry->prepare("select * from reservation");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
}


void MainWindow::on_pushButton_chercher_clicked()
{

            QString CIN= ui->lineEdit->text() ;
            ui->tableView->setModel(tempclient.cherchercin(CIN));


}


void MainWindow::on_radioButton_clicked()
{
    Connection conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db);
    qry->prepare("select * from reservation ORDER BY CIN ");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
}

void MainWindow::on_pushButton_clicked()
{
      ui->tableView->setModel(tempclient.afficher());
}

void MainWindow::on_radioButton_5_clicked()
{
    Connection conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db);
    qry->prepare("select * from reservation ORDER BY Prenom");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
}

void MainWindow::on_radioButton_4_clicked()
{
    Connection conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db);
    qry->prepare("select * from reservation ORDER BY Nom");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
}

void MainWindow::on_radioButton_6_clicked()
{
    Connection conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db);
    qry->prepare("select * from reservation ORDER BY Date");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
}

void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::on_pushButton_ajouter_2_clicked()
{
    ajouter_2 ajouter;
    ajouter.setModal(true);
    ajouter.exec();

    Connection conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db);
    qry->prepare("select * from tables");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
}

void MainWindow::on_pushButton_modifier_2_clicked()
{
    modifier_2 modifier;
    modifier.setModal(true);
    modifier.exec();

    Connection conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db);
    qry->prepare("select * from tables");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
}

void MainWindow::on_pushButton_supprimer_2_clicked()
{
    supprimer_2 supp;
    supp.setModal(true);
    supp.exec();

    Connection conn;
    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery * qry=new QSqlQuery(conn.db);
    qry->prepare("select * from tables");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);

}

void MainWindow::on_sendBtn_2_clicked()
{
        connect(ui->sendBtn_2, SIGNAL(clicked()),this, SLOT(sendMail()));
        connect(ui->exitBtn_2, SIGNAL(clicked()),this, SLOT(close()));
        connect(ui->browseBtn_3, SIGNAL(clicked()), this, SLOT(browse()));

}

void MainWindow::on_pushButton_mail_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::on_pushButton_retour_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}




