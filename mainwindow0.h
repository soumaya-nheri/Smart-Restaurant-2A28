#ifndef MAINWINDOW0_H
#define MAINWINDOW0_H
#include "mainwindow.h"
#include <QMainWindow>
#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>

namespace Ui {
class MainWindow0;
}

class MainWindow0 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow0(QWidget *parent = nullptr);
    ~MainWindow0();


private slots:
    void on_pushButton_clicked();
    void showTime();

private:
    Ui::MainWindow0 *ui;
    MainWindow * home;
};

#endif // MAINWINDOW0_H
