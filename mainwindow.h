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
    void on_ajouter_staff_clicked();

    void on_modifier_staff_clicked();

    void on_supprimer_staff_clicked();

    void on_ajouter_clicked();

    void on_pushButtonSuppr_clicked();

    void on_pushButtonEdit_clicked();

    void on_pushButtonPDF_2_clicked();

    void on_rechercher_staff_clicked();

    void on_ajouter_planning_clicked();

    void on_recherche_staff_textChanged(const QString &arg1);

    void on_pushButtonRechercherConge_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    staff tmpstaff;
};
#endif // MAINWINDOW_H
