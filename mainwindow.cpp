#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView_staff->setModel(tmpstaff.afficher());
    ui->tableView_staff->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_staff->setSelectionMode(QAbstractItemView::SingleSelection);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_staff_clicked()
{
    QString cin=ui->cin_staff->text();
    QString nom=ui->nom_staff->text();
    QString prenom=ui->prenom_staff->text();
    QString email=ui->email_staff->text();
    QString telephone=ui->tel_staff->text();
    QString login=ui->login_staff->text();
    QString password=ui->pass_staff->text();
    QString role=ui->role_staff->currentText();
    int salaire=ui->salaire_staff->text().toInt();

    staff staff(cin,nom,prenom,email,telephone,login,password,role,salaire);
    if (staff.ajouter())
    {
        ui->tableView_staff->setModel(tmpstaff.afficher());

    }
    else
    {
        qDebug() << "Erreur d'ajout.";
    }

}

void MainWindow::on_modifier_staff_clicked()
{
    if (ui->modifier_staff->isChecked())
    {

        ui->modifier_staff->setText(tr("Modifiable"));
        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("staff");
        tableModel->select();
        ui->tableView_staff->setModel(tableModel);
    }
    else
    {
        ui->modifier_staff->setText(tr("Modifier"));
        ui->tableView_staff->setModel(tmpstaff.afficher());

    }
}

void MainWindow::on_supprimer_staff_clicked()
{
    QItemSelectionModel *select = ui->tableView_staff->selectionModel();

    QString cin =select->selectedRows(0).value(0).data().toString();

    if(tmpstaff.supprimer(cin))
    {
        ui->tableView_staff->setModel(tmpstaff.afficher());

    }

}
