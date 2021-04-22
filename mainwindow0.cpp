#include "mainwindow0.h"
#include "ui_mainwindow0.h"

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
    QString username = ui->line_username->text();
    QString password = ui->line_password->text();

    if(username == "admin" && password=="admin"){
        ui->line_username->clear();
        ui->line_password->clear();
        hide();
        home = new class MainWindow(this);
        home->show();
    } else {
        ui->incorrect->setText("Nom d'utilisateur ou mot de passe est incorrect ");
        ui->line_username->clear();
        ui->line_password->clear();
    }
}
