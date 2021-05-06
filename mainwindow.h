#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <src/SmtpMime>
#include <QtNetwork>
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
#include<fclient.h>
#include<flivraison.h>
#include "planning.h"
#include"client.h"
#include"tables.h"
#include "evenement.h"
#include "offre.h"
#include "commande.h"
#include "plat.h"
#include "produit.h"
#include "fournisseur.h"
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
#include<QSystemTrayIcon> //notification
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
    QSystemTrayIcon *mysystem1;

private slots:
    void mailSent(QString);

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

    //bacim

    void on_pushButtonAjouter_4_clicked();

    void on_pushButtonAjouter_evenement_4_clicked();

    void on_pushButtonSupprimer_4_clicked();

    void on_pushButtonAjouterOffre_4_clicked();



    void on_pushButtonAfficherOffre_4_clicked();

    void on_pushButtonAfficher_4_clicked();



    void on_pushButtonAjouter_Offre1_4_clicked();

    void on_pushButtonRetour_menu_4_clicked();

    void on_pushButtonSupprimer_offre_4_clicked();

    void on_pushButtonRetour_17_clicked();

    void on_pushButtonRetour_18_clicked();

    void on_pushButtonRetour_16_clicked();

    void on_pushButtonAnnuler_4_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_33_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_32_clicked();

    void on_pushButtonRetour_4_clicked();

    void on_pushButton_35_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_36_clicked();

    void on_pushButton_gestionnouv_clicked();

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

      void on_pushButton_stat_clicked();

      void on_pushButton_gestionstock_clicked();

      void on_pushButton_mailCom_clicked();

      //yassine
      void on_pushButton_clicked();


      void on_tableView_activated(const QModelIndex &index);

      void on_pushButton_3_clicked();

      void on_pushButton_4_clicked();

      void on_pushButton_5_clicked();



      void on_pushButton_6_clicked();



      void on_pushButton_7_clicked();

      void on_pushButton_8_clicked();

      void on_pushButton_14_clicked();

      void on_tableView_2_activated(const QModelIndex &index);

      void on_pushButton_17_clicked();

      void on_pushButton_13_clicked();

      void on_lineEdit_2_textChanged(const QString &arg1);

      void on_pushButton_12_clicked();

      void on_pushButton_16_clicked();

      void on_pushButton_15_clicked();

      void on_pushButton_gestionclient_clicked();

      void on_pushButton_retour_2_clicked();

      void on_pushButton_retour_clicked();

      void on_pushButton_18_clicked();

      void on_pushButton_19_clicked();

      void on_pushButton_retour_5_clicked();

      void on_pushButton_20_clicked();

      void on_pushButton_21_clicked();

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
    Evenement evenementtmp;
    Offre offretmp;
    staff tmpstaff;
    planning tmplanning;
    QSqlQuery qry,qry1;
    Produit tempproduit;
    Fournisseur tempfournisseur;
    fclient tmpclient;
    flivraison tmplivraison;

};
#endif // MAINWINDOW_H
