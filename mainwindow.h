#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QWidget>
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QRegularExpression>
#include <QTableWidgetItem>
#include <QDebug>
#include <QSqlTableModel>
#include <QAbstractItemView>
#include <QRegExp>
#include <QFileDialog>
#include <QSortFilterProxyModel>
#include <QTextDocument>
#include <QPropertyAnimation>
#include "database.h"
#include "staff.h"
#include "planning.h"
#include"client.h"
#include"tables.h"
#include "commande.h"
#include "plat.h"
#include <QMainWindow>
#include<QPropertyAnimation> //animation
#include<QMediaPlayer> //music
#include<QLineEdit>
#include <QApplication>
#include <QMessageBox>
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QWidget>
#include<QTabWidget>
#include<QFileSystemModel>
#include <QSystemTrayIcon> //notification
#include<QtPrintSupport/QPrinter> //imprimer
#include<QtPrintSupport/QPrintDialog> //imprimer
#include<QCompleter> //recherche completer
#include<QSqlRecord>
#include<QtCharts> //stat
#include<QChartView> //stat
#include<QPieSeries> //stat
#include<QPieSlice> //stat
class Connection1
{
public:
    QSqlDatabase db1;
public:
    Connection1();
    bool createconnection1();
    void closeconnection1();
};
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void sendMail();
    void mailSent(QString);
    void browse();

    void on_pushButton_ajoutercom_clicked();

    void on_pushButton_annulerCom_clicked();

    void on_pushButton_imprimerCom_clicked();

    void on_pushButton_rechercherCom_clicked();

    void on_radioButton_triedateCom_clicked();

    void on_radioButton_trietypeCom_clicked();

    void on_radioButton_trieidstaff_clicked();

    void on_pushButton_modifierCom_clicked();

    void on_pushButton_vaModificationCom_clicked();

    void on_pushButton_supprimercom_clicked();

    void on_pushButton_statCom_clicked();

    void on_pushButton_ajouterplat_clicked();

    void on_pushButton_annulerPlat_clicked();

    void on_pushButton_rechercherPlat_clicked();

    void on_radioButton_trienomPlat_clicked();

    void on_radioButton_TriedesPlat_clicked();

    void on_radioButton_trieprixPlat_clicked();

    void on_pushButton_modifierPlat_clicked();

    void on_pushButton_vaModificationPlat_clicked();

    void on_pushButton_imprimerPlat_clicked();

    void on_pushButton_supprimerplat_clicked();

    void on_checkBox_traduction_clicked();

    void on_pushButton_ajoutertab_2_clicked();

    void on_pushButton_modifiertab_2_clicked();

    void on_pushButton_supprimertab_2_clicked();

    void on_pushButton_cherchertab_2_clicked();

    void on_pushButton_table_2_clicked();

    void on_pushButton_ajouterres_2_clicked();

    void on_pushButton_modifierres_2_clicked();

    void on_pushButton_supprimerres_2_clicked();

    void on_pushButton_mail_2_clicked();

    void on_pushButton_listeres_2_clicked();

    void on_radioButton_tricin_2_clicked();

    void on_radioButton_triprenom_2_clicked();

    void on_radioButton_trinom_2_clicked();

    void on_pushButton_chercherres_2_clicked();

    void on_pushButton_res_2_clicked();

    void on_sendBtn_3_clicked();

    void on_ajouter_staff_2_clicked();

    void on_modifier_staff_2_clicked();

    void on_supprimer_staff_2_clicked();

    void on_ajouter_2_clicked();

    void on_pushButtonSuppr_2_clicked();

    void on_pushButtonEdit_2_clicked();

    void on_pushButtonPDF_3_clicked();

    void on_rechercher_staff_2_clicked();

    void on_ajouter_planning_2_clicked();

    void on_recherche_staff_2_textChanged(const QString &arg1);

    void on_pushButtonRechercherConge_2_clicked();

    void on_pushButton_2_clicked();

    void on_supprimer_planning_2_clicked();

    void on_pushButton_gestioncom_clicked();

    void on_pushButton_gestionres_clicked();

    void on_pushButton_retourCom_clicked();

    void on_pushButton_retour_3_clicked();

    void on_pushButton_retour_6_clicked();

    void on_pushButton_gestionstaff_clicked();

    void on_tableViewConge_2_activated(const QModelIndex &index);

private:
Ui::MainWindow *ui;
    Commande Com;
    Plat P;
    QMediaPlayer *click; //music
    QMediaPlayer *music; //music
    QTabWidget * tab;
    QSystemTrayIcon *mysystem; //notification
    QPropertyAnimation * animation; //animation
    Client tempclient;
    QStringList files;
    Tables temptable;
    staff tmpstaff;
    planning tmplanning;
    QSqlQuery qry,qry1;

};
#endif // MAINWINDOW_H
