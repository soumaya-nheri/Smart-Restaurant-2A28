#ifndef SUPPRIMER_H
#define SUPPRIMER_H

#include <QDialog>
#include "produit.h"
#include <QMessageBox>

namespace Ui {
class supprimerproduit;
}

class supprimerproduit : public QDialog
{
    Q_OBJECT

public:
    explicit supprimerproduit(QWidget *parent = nullptr);
    ~supprimerproduit();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::supprimerproduit *ui;
       Produit temp;
};

#endif // SUPPRIMER_H
