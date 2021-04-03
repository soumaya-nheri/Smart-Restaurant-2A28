#include "mainwindow2.h"
#include "ui_mainwindow2.h"
#include <QPixmap>
#include <QMessageBox>

MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2)
{
    ui->setupUi(this);
}

MainWindow2::~MainWindow2()
{
    delete ui;
}

void MainWindow2::on_pushButton_2_clicked()
{
    QString username = ui->line_username_2->text();
    QString password = ui->line_password_2->text();

    if(username == "admin" && password=="admin"){
        ui->line_username_2->clear();
        ui->line_password_2->clear();
        hide();
        mainwindow = new class MainWindow(this);
        mainwindow->show();
    } else {
        ui->incorrect->setText("Nom d'utilisateur ou mot de passe est incorrect ");
        ui->line_username_2->clear();
        ui->line_password_2->clear();
    }

}
