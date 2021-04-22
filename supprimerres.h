#ifndef SUPPRIMERRES_H
#define SUPPRIMERRES_H

#include <QDialog>
#include "client.h"
#include <QMessageBox>

namespace Ui {
class supprimerres;
}

class supprimerres : public QDialog
{
    Q_OBJECT

public:
    explicit supprimerres(QWidget *parent = nullptr);
    ~supprimerres();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::supprimerres *ui;
       Client temp;
};

#endif // SUPPRIMERRES_H
