#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "evenement.h"
#include "connexion.h"
#include "offre.h"
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>

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
    void on_pushButtonAjouter_clicked();

    void on_pushButtonAjouter_evenement_clicked();

    void on_pushButtonSupprimer_clicked();

    void on_pushButtonAjouterOffre_clicked();



    void on_pushButtonAfficherOffre_clicked();

    void on_pushButtonAfficher_clicked();



    void on_pushButtonAjouter_Offre1_clicked();

    void on_pushButtonRetour_menu_clicked();

    void on_pushButtonSupprimer_offre_clicked();

    void on_pushButtonRetour_2_clicked();

    void on_pushButtonRetour_5_clicked();

    void on_pushButtonRetour_4_clicked();

    void on_pushButtonAnnuler_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButtonRetour_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();

private:
    Ui::MainWindow *ui;
    Evenement evenementtmp;
    Offre offretmp;
    Connection db;
};
#endif // MAINWINDOW_H
