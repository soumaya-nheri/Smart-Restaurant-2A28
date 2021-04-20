#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPropertyAnimation>
#include<QMediaPlayer>
#include "commande.h"
#include "plat.h"
#include"stat.h"
#include<QLineEdit>
#include <QSystemTrayIcon>
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
    QMediaPlayer *click;
    QMediaPlayer *music;
    QTabWidget * tab;
    stat S;
    QSystemTrayIcon *mysystem;
    //QPropertyAnimation * animation;

};
#endif // MAINWINDOW_H
