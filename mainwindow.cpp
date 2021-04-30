#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "smtp.h"
#include <QtPrintSupport/QPrinter>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QIntValidator *roll = new QIntValidator(100000,999999);
    ui->pushButton_10->hide();
    ui->plainTextEdit_2->hide();

    ui->lineEditId->setValidator(roll);
    ui->lineEditIdOffre->setValidator(roll);
    ui->tableView->setModel(evenementtmp.show_evenements());
     ui->tableView_2->setModel(offretmp.show_offres());
    QFile file1("C:/Users/bacim/Desktop/Historique.txt");
   if (!file1.open(QIODevice::ReadOnly))
   {
       QMessageBox::information(0,"info",file1.errorString());
   }
   QTextStream in (&file1);
  ui->textBrowser->setText(in.readAll());

    ui->tabWidget1->setCurrentIndex(0);
    QPieSeries *series = new QPieSeries();
        QSqlQuery q("select prix,count(*) as nombre from evenements group by prix");


         while(q.next())
         {series->append(q.value(0).toString()+": "+q.value(1).toString(),q.value(1).toInt());}

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Statistiques des prix des evenements");
        chart->setBackgroundBrush(Qt::transparent);
        QChartView *chartview = new QChartView(chart);
        chartview->setRenderHint(QPainter::Antialiasing);
        chartview->setParent(ui->horizontalFrame);
        chartview->resize(400,300);

        chart->setAnimationOptions(QChart::AllAnimations);
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignRight);
        series->setLabelsVisible(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonAjouter_clicked()
{
    ui->tabWidget1->setCurrentIndex(2);

}

void MainWindow::on_pushButtonAjouter_evenement_clicked()
{


    Evenement e(ui->lineEditId->text().toInt(),ui->lineEditNom->text(), ui->lineEditPrix->text().toFloat(),ui->dateEdit1->date().toString(),ui->textEditDescription->toPlainText());
    bool test = e.add_evenement();
    QFile file("C:/Users/bacim/Desktop/Historique.txt");
            if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                return;

            QTextStream cout(&file);
    if (test)

    {
        ui->lineEditNom->setText("");
        ui->lineEditId->setText("");
    ui->lineEditPrix->setText("");
        ui->textEditDescription->setText("");

       QString message2="Vous avez ajouté un evenement\n";
            cout << message2;
            QFile file("C:/Users/bacim/Desktop/Historique.txt");
           if (!file.open(QIODevice::ReadOnly))
           {
               QMessageBox::information(0,"info",file.errorString());
           }
           QTextStream in (&file);
          ui->textBrowser->setText(in.readAll());
        QMessageBox::information(nullptr,QObject::tr("Add Evenement"),QObject::tr("Evenement ajouté avec success\n click ok to exit"),QMessageBox::Ok);
        ui->tableView->setModel(evenementtmp.show_evenements());
    }
    else

    {

        QMessageBox::warning(nullptr,QObject::tr("Add Evenement"),QObject::tr("Evenement n a pas ete ajouté\n click ok to exit"),QMessageBox::Ok);

    }
}

void MainWindow::on_pushButtonSupprimer_clicked()
{
    int row=ui->tableView->selectionModel()->currentIndex().row();
    int id=ui->tableView->model()->index(row,0).data().toInt();
    bool  test = evenementtmp.delete_evenement(id);
    QFile file("C:/Users/bacim/Desktop/Historique.txt");
            if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                return;

            QTextStream cout(&file);
    if (test)

    {



   QString message2="Vous avez supprimé un evenement\n";
        cout << message2;
        QFile file("C:/Users/bacim/Desktop/Historique.txt");
       if (!file.open(QIODevice::ReadOnly))
       {
           QMessageBox::information(0,"info",file.errorString());
       }
       QTextStream in (&file);
      ui->textBrowser->setText(in.readAll());
        QMessageBox::information(nullptr,QObject::tr("delete Evenement"),QObject::tr("Evenement supprime avec success\n click ok to exit"),QMessageBox::Ok);
        ui->tableView->setModel(evenementtmp.show_evenements());
    }
    else

    {
        QMessageBox::warning(nullptr,QObject::tr("delete Evenement"),QObject::tr("Evenement n a pas ete supprime\n click ok to exit"),QMessageBox::Ok);

    }

}

void MainWindow::on_pushButtonAjouterOffre_clicked()
{
     ui->tabWidget1->setCurrentIndex(3);
}


void MainWindow::on_pushButtonAfficherOffre_clicked()
{
    ui->tabWidget1->setCurrentIndex(4);
}

void MainWindow::on_pushButtonAfficher_clicked()
{
     ui->tabWidget1->setCurrentIndex(1);
}


void MainWindow::on_pushButtonAjouter_Offre1_clicked()
{
    Offre o(ui->lineEditIdOffre->text().toInt(),ui->lineEditNomOffre->text(), ui->lineEditPrixOffre->text().toDouble(),ui->textEditDescriptionOffre->toPlainText());
    bool test = o.add_offre();
    QFile file("C:/Users/bacim/Desktop/Historique.txt");
            if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                return;

            QTextStream cout(&file);
    if (test)

    {




QString message2="Vous avez ajouté un offre\n";
cout << message2;
QFile file("C:/Users/bacim/Desktop/Historique.txt");
if (!file.open(QIODevice::ReadOnly))
{
   QMessageBox::information(0,"info",file.errorString());
}
QTextStream in (&file);
ui->textBrowser->setText(in.readAll());
        ui->lineEditNomOffre->setText("");
        ui->lineEditIdOffre->setText("");
    ui->lineEditPrixOffre->setText("");
        ui->textEditDescriptionOffre->setText("");
        QMessageBox::information(nullptr,QObject::tr("Add Offre"),QObject::tr("Offre ajouté avec success\n click ok to exit"),QMessageBox::Ok);
        ui->tableView_2->setModel(offretmp.show_offres());
    }
    else

    {
        QMessageBox::warning(nullptr,QObject::tr("Add Offre"),QObject::tr("Offre n a pas ete ajouté\n click ok to exit"),QMessageBox::Ok);

    }
}


void MainWindow::on_pushButtonRetour_menu_clicked()
{
     ui->tabWidget1->setCurrentIndex(0);
}

void MainWindow::on_pushButtonSupprimer_offre_clicked()
{
    int row=ui->tableView_2->selectionModel()->currentIndex().row();
    int id=ui->tableView_2->model()->index(row,0).data().toInt();
    bool  test = offretmp.delete_offre(id);
    QFile file("C:/Users/bacim/Desktop/Historique.txt");
            if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                return;

            QTextStream cout(&file);
    if (test)

    {




QString message2="Vous avez supprimé un offre\n";
cout << message2;
QFile file("C:/Users/bacim/Desktop/Historique.txt");
if (!file.open(QIODevice::ReadOnly))
{
QMessageBox::information(0,"info",file.errorString());
}
QTextStream in (&file);
ui->textBrowser->setText(in.readAll());
        QMessageBox::information(nullptr,QObject::tr("delete Offre"),QObject::tr("Offre supprime avec success\n click ok to exit"),QMessageBox::Ok);
        ui->tableView_2->setModel(offretmp.show_offres());
    }
    else

    {
        QMessageBox::warning(nullptr,QObject::tr("delete Offre"),QObject::tr("Offre n a pas ete supprime\n click ok to exit"),QMessageBox::Ok);

    }
}

void MainWindow::on_pushButtonRetour_2_clicked()
{
    ui->tabWidget1->setCurrentIndex(0);
}

void MainWindow::on_pushButtonRetour_5_clicked()
{
     ui->tabWidget1->setCurrentIndex(0);
}

void MainWindow::on_pushButtonRetour_4_clicked()
{
    Offre o(ui->lineEditIdOffre->text().toInt(),ui->lineEditNomOffre->text(), ui->lineEditPrixOffre->text().toDouble(),ui->textEditDescriptionOffre->toPlainText());
    bool test = o.update_offre(ui->lineEditIdOffre->text().toInt());
    QFile file("C:/Users/bacim/Desktop/Historique.txt");
            if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                return;

            QTextStream cout(&file);
    if (test)

    {




QString message2="Vous avez modifié un offre\n";
cout << message2;
QFile file("C:/Users/bacim/Desktop/Historique.txt");
if (!file.open(QIODevice::ReadOnly))
{
QMessageBox::information(0,"info",file.errorString());
}
QTextStream in (&file);
ui->textBrowser->setText(in.readAll());
        ui->lineEditNomOffre->setText("");
        ui->lineEditIdOffre->setText("");
    ui->lineEditPrixOffre->setText("");
        ui->textEditDescriptionOffre->setText("");
        QMessageBox::information(nullptr,QObject::tr("Update Offre"),QObject::tr("Offre modifié avec success\n click ok to exit"),QMessageBox::Ok);
        ui->tableView_2->setModel(offretmp.show_offres());
    }
    else

    {
        QMessageBox::warning(nullptr,QObject::tr("Update Offre"),QObject::tr("Offre n a pas ete modifié\n click ok to exit"),QMessageBox::Ok);

    }
}

void MainWindow::on_pushButtonAnnuler_clicked()
{
    Evenement e(ui->lineEditId->text().toInt(),ui->lineEditNom->text(), ui->lineEditPrix->text().toDouble(),ui->dateEdit1->date().toString(),ui->textEditDescription->toPlainText());
    bool test = e.update_evenement(ui->lineEditId->text().toInt());
    QFile file("C:/Users/bacim/Desktop/Historique.txt");
            if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                return;

            QTextStream cout(&file);
    if (test)

    {




QString message2="Vous avez modifié un evenement\n";
    cout << message2;
    QFile file("C:/Users/bacim/Desktop/Historique.txt");
   if (!file.open(QIODevice::ReadOnly))
   {
       QMessageBox::information(0,"info",file.errorString());
   }
   QTextStream in (&file);
  ui->textBrowser->setText(in.readAll());
        ui->lineEditNom->setText("");
        ui->lineEditId->setText("");
    ui->lineEditPrix->setText("");
        ui->textEditDescription->setText("");
        QMessageBox::information(nullptr,QObject::tr("Update Evenement"),QObject::tr("Evenement modifié avec success\n click ok to exit"),QMessageBox::Ok);
        ui->tableView->setModel(evenementtmp.show_evenements());
    }
    else

    {
        QMessageBox::warning(nullptr,QObject::tr("Update Evenement"),QObject::tr("Evenement n a pas ete modifié\n click ok to exit"),QMessageBox::Ok);

    }
}

void MainWindow::on_pushButton_clicked()
{
    int row=ui->tableView->selectionModel()->currentIndex().row();
    int id=ui->tableView->model()->index(row,0).data().toInt();
    QString id_str=QString::number(id);
    ui->lineEditId->setText(id_str);
    ui->tabWidget1->setCurrentIndex(2);

}

void MainWindow::on_pushButton_2_clicked()
{
    int row=ui->tableView_2->selectionModel()->currentIndex().row();
    int id=ui->tableView_2->model()->index(row,0).data().toInt();
    QString id_str=QString::number(id);
    ui->lineEditIdOffre->setText(id_str);
    ui->tabWidget1->setCurrentIndex(3);

}

void MainWindow::on_pushButton_3_clicked()
{
     ui->tableView->setModel(evenementtmp.tri_evenements(ui->comboBox_2->currentText()));
}

void MainWindow::on_pushButton_4_clicked()
{
     ui->tableView->setModel(evenementtmp.find_evenements(ui->comboBox->currentText(),ui->lineEditRech->text()));
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->tableView->setModel(evenementtmp.show_evenements());
}

void MainWindow::on_pushButton_6_clicked()
{
    Smtp* smtp = new Smtp("bacim.oueslati@esprit.tn", "191JMT2993", "smtp.gmail.com", 465);
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
        smtp->sendMail("bacim.oueslati@esprit.tn",ui->lineEdit->text(),ui->lineEdit_2->text(),ui->plainTextEdit->toPlainText());
}

void MainWindow::on_pushButton_7_clicked()
{
    QString strStream;
                       QTextStream out(&strStream);

                        const int rowCount = ui->tableView->model()->rowCount();
                        const int columnCount = ui->tableView->model()->columnCount();
                       out <<  "<html>\n"
                       "<head>\n"
                                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                        <<  QString("<title>%1</title>\n").arg("strTitle")
                                        <<  "</head>\n"
                                        "<body bgcolor=#ffffff link=#5000A0>\n"

                                       //     "<align='right'> " << datefich << "</align>"
                                        "<center> <H1>Liste des evenements</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                    // headers
                                    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                    out<<"<cellspacing=10 cellpadding=3>";
                                    for (int column = 0; column < columnCount; column++)
                                        if (!ui->tableView->isColumnHidden(column))
                                            out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                                    out << "</tr></thead>\n";

                                    // data table
                                    for (int row = 0; row < rowCount; row++) {
                                        out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                        for (int column = 0; column < columnCount; column++) {
                                            if (!ui->tableView->isColumnHidden(column)) {
                                                QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                                                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                            }
                                        }
                                        out << "</tr>\n";
                                    }
                                    out <<  "</table> </center>\n"
                                        "</body>\n"
                                        "</html>\n";

                              QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                                if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                               QPrinter printer (QPrinter::PrinterResolution);
                                printer.setOutputFormat(QPrinter::PdfFormat);
                               printer.setPaperSize(QPrinter::A4);
                              printer.setOutputFileName(fileName);

                               QTextDocument doc;
                                doc.setHtml(strStream);
                                doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                                doc.print(&printer);
}

void MainWindow::on_pushButton_8_clicked()
{
    QTableView *table;
           table = ui->tableView_2;

           QString filters("CSV files (.csv);;All files (.*)");
           QString defaultFilter("CSV files (*.csv)");
           QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                              filters, &defaultFilter);
           QFile file(fileName);

           QAbstractItemModel *model =  table->model();
           if (file.open(QFile::WriteOnly | QFile::Truncate)) {
               QTextStream data(&file);
               QStringList strList;
               for (int i = 0; i < model->columnCount(); i++) {
                   if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                       strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                   else
                       strList.append("");
               }
               data << strList.join(";") << "\n";
               for (int i = 0; i < model->rowCount(); i++) {
                   strList.clear();
                   for (int j = 0; j < model->columnCount(); j++) {

                       if (model->data(model->index(i, j)).toString().length() > 0)
                           strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                       else
                           strList.append("");
                   }
                   data << strList.join(";") + "\n";
               }
               file.close();
               QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
           }
}

void MainWindow::on_pushButtonRetour_clicked()
{

}

void MainWindow::on_pushButton_10_clicked()
{
    QFile file("C:/Users/bacim/Desktop/notes.txt");
            if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                return;
            QTextStream cout(&file);
QString message2="- "+ui->plainTextEdit_2->toPlainText() +"\n" ;
    cout << message2;
    ui->plainTextEdit_2->setPlainText("");
    ui->pushButton_10->hide();
    ui->plainTextEdit_2->hide();
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->pushButton_10->show();
    ui->plainTextEdit_2->show();
}

void MainWindow::on_pushButton_11_clicked()
{
    if (ui->comboBox_3->currentText()=="Dark mode")
     {
        ui->centralwidget->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:1, y1:0, x2:1, y2:1, stop:0 black,stop:1 rgba(56, 63, 77, 255));");
    }
    if (ui->comboBox_3->currentText()=="Light mode")
     {
        ui->centralwidget->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:1, y1:0, x2:1, y2:1, stop:0 #d5d0e5,stop:1 #f3e6e8);color:black;");

    }
    if (ui->comboBox_3->currentText()=="Normal mode")
     {
        ui->centralwidget->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:1, y1:0, x2:1, y2:1, stop:0 rgba(102, 115, 140, 255),stop:1 rgba(56, 63, 77, 255));QPushButton        {            background-color: qlineargradient(spread:repeat, x1:0.486, y1:0, x2:0.505, y2:1, stop:0.00480769 rgba(170, 0, 0, 255),stop:1 rgba(122, 0, 0, 255));            color: #ffffff;            font-weight: bold;            border-style: solid;            border-width: 1px;           border-radius: 3px;         border-color: #051a39;            padding: 5px;                }");

    }
}
