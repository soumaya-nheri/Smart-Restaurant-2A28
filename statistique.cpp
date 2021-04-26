#include "statistique.h"
#include "ui_statistique.h"
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
#include <QWidget>
#include <QSqlQuery>
Statistique::Statistique(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Statistique)
{
    ui->setupUi(this);
}

Statistique::~Statistique()
{
    delete ui;
}

void Statistique::make()
{
    int regio;
   int non_regio;
   int total;
   QString regionale;
   QString non_regionale;
   QSqlQuery q;

   q.prepare("SELECT COUNT(id_com) FROM commandes where type_com='emporter' ");
   q.exec();
   q.first() ;
   regio=(q.value(0).toInt());

   q.prepare("SELECT COUNT(id_com) FROM commandes where type_com='sur place' ");
   q.exec();
   q.first() ;
   non_regio=(q.value(0).toInt());

   q.prepare("SELECT COUNT(id_com) FROM commandes ");
   q.exec();
   q.first() ;
   total=(q.value(0).toInt());

   regio=((double)regio/(double)total)*100;
   non_regio=100-regio;

   regionale= QString::number(regio);
   non_regionale=QString::number(non_regio);
   QPieSeries *series;
    series= new  QPieSeries();
    series->append("emporter"+regionale+"%",regio);
    series->append("sur place"+non_regionale+"%",non_regio);
    QPieSlice *slice0 = series->slices().at(0);
     slice0->setLabelVisible();

     QPieSlice *slice1 = series->slices().at(1);
        slice1->setExploded();
        slice1->setLabelVisible();
        slice1->setPen(QPen(Qt::green, 3));
        slice1->setBrush(Qt::darkYellow);

         QChart *chart = new QChart();
         chart->addSeries(series);
         chart->setTitle("Statistique du type de commandes ");
         chart->legend()->show();
         QChartView *chartView = new QChartView(chart);
         chartView->setRenderHint(QPainter::Antialiasing);
         ui->verticalLayout->addWidget(chartView);

}
//verticalLayout
