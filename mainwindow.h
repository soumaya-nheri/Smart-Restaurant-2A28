#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQueryModel>
#include "produit.h"
#include <QFileDialog>
#include <QDialog>
#include "fournisseur.h"

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





    void on_pushButton_ajouterproduit_clicked();

    void on_pushButton_modifierproduit_clicked();

    void on_pushButton_supprimerproduit_clicked();

    void on_pushButtonproduit_clicked();

    void on_radioButton_quantitepr_clicked();

    void on_radioButton_pripr_clicked();

    void on_radioButton_typepr_clicked();

    void on_pushButton_chercherproduit_clicked();

    void on_pushButton_imprimerproduit_clicked();

    void on_pushButton_ajouter_fournisseur_clicked();

    void on_pushButton_modifier_fournisseur_clicked();

    void on_pushButton_supprimer_fournisseur_clicked();

    void on_pushButton_afficherfournisseur_clicked();

private:
    Ui::MainWindow *ui;
    Produit tempproduit;
    QStringList files;
    Fournisseur tempfournisseur;
};
#endif // MAINWINDOW_H
