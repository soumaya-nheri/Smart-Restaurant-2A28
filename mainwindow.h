#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private:
    Ui::MainWindow *ui;
    staff tmpstaff;
};
#endif // MAINWINDOW_H
