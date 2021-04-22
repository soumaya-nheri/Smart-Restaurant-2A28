#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQueryModel>
#include "client.h"
#include <QFileDialog>
#include <QDialog>
#include "tables.h"

class Connection
{
public:
    QSqlDatabase db;
public:
    Connection();
    bool createconnection();
    void closeconnection();
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void sendMail();
    void mailSent(QString);
    void browse();



    void on_pushButton_mail_clicked();






    void on_sendBtn_2_clicked();





    void on_pushButton_retour_4_clicked();







    void on_pushButton_ajouterres_clicked();

    void on_pushButton_modifierres_clicked();

    void on_pushButton_supprimerres_clicked();

    void on_pushButton_chercherres_clicked();

    void on_pushButton_listeres_clicked();

    void on_pushButton_res_clicked();

    void on_radioButton_tridate_clicked();

    void on_radioButton_triprenom_clicked();

    void on_radioButton_trinom_clicked();

    void on_radioButton_tricin_clicked();

    void on_pushButton_cherchertab_clicked();

    void on_pushButton_ajoutertab_clicked();

    void on_pushButton_modifiertab_clicked();

    void on_pushButton_supprimertab_clicked();

    void on_pushButton_table_clicked();

private:
    Ui::MainWindow *ui;
    Client tempclient;
    QStringList files;
    Tables temptable;
};
#endif // MAINWINDOW_H
