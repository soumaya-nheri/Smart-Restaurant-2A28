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

    void on_pushButton_ajouter_clicked();

    void on_pushButton_modifier_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_mail_clicked();

    void on_pushButton_retour_clicked();

    void on_pushButton_chercher_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_clicked();

    void on_pushButton_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_6_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_ajouter_2_clicked();

    void on_pushButton_modifier_2_clicked();

    void on_pushButton_supprimer_2_clicked();

    void on_sendBtn_2_clicked();

    void on_browseBtn_2_clicked();

    void on_pushButton_supprimer_3_clicked();

    void on_pushButton_retour_4_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    Client tempclient;
    QStringList files;
};
#endif // MAINWINDOW_H
