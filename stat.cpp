#include "stat.h"
#include "ui_stat.h"
#include <QString>
#include<qsqlquery.h>

Stat::Stat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stat)
{
    ui->setupUi(this);
}

Stat::~Stat()
{
    delete ui;
}



void Stat::made()
{
         int regio;
        int non_regio;
        int total;
        QString regionale;
        QString non_regionale;
        QSqlQuery q;

        q.prepare("SELECT COUNT(id_com) FROM commandes where type_com='livraison' ");
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
         series->append("livraison"+regionale+"%",regio);
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
              chart->setTitle("Stat sur type d'evenement ");
              chart->legend()->show();
              QChartView *chartView = new QChartView(chart);
              chartView->setRenderHint(QPainter::Antialiasing);
              ui->verticalLayout->addWidget(chartView);

}
