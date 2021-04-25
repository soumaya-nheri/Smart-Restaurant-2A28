#ifndef SUPPRIMER_FOURNISSEUR_H
#define SUPPRIMER_FOURNISSEUR_H

#include <QDialog>

namespace Ui {
class supprimer_fournisseur;
}

class supprimer_fournisseur : public QDialog
{
    Q_OBJECT

public:
    explicit supprimer_fournisseur(QWidget *parent = nullptr);
    ~supprimer_fournisseur();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::supprimer_fournisseur *ui;

};

#endif // SUPPRIMER_FOURNISSEUR_H
