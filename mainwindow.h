#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "commande.h"
#include "plat.h"
#include"arduino.h"
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

    void on_checkBox_traduction_clicked();

//arduino
    void update_label();

//commandes
    void on_pushButton_ajoutercom_clicked();

    void on_pushButton_annulerCom_clicked();

    void on_pushButton_modifierCom_clicked();

    void on_pushButton_vaModificationCom_clicked();

    void on_pushButton_supprimercom_clicked();

    void on_pushButton_rechercherCom_clicked();

    void on_radioButton_triedateCom_clicked();

    void on_radioButton_trietypeCom_clicked();

    void on_radioButton_trieidstaff_clicked();

    void on_pushButton_imprimerCom_clicked();

    void on_pushButton_statCom_clicked();

//plats
    void on_pushButton_ajouterplat_clicked();

    void on_pushButton_annulerPlat_clicked();

    void on_pushButton_modifierPlat_clicked();

    void on_pushButton_vaModificationPlat_clicked();

    void on_pushButton_supprimerplat_clicked();

    void on_pushButton_imprimerPlat_clicked();

    void on_radioButton_trienomPlat_clicked();

    void on_radioButton_TriedesPlat_clicked();

    void on_radioButton_trieprixPlat_clicked();

    void on_pushButton_rechercherPlat_clicked();




private:
    Ui::MainWindow *ui;
    Commande Com;
    Plat P;
    QMediaPlayer *click; //music
    QMediaPlayer *music; //music
    QTabWidget * tab;
    QSystemTrayIcon *mysystem; //notification
    QPropertyAnimation * animation; //animation
    QByteArray data; //arduino donnee reçu
    Arduino A; //arduino

};
#endif // MAINWINDOW_H
