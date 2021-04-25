#ifndef AJOUTER_FOURNISSEUR_H
#define AJOUTER_FOURNISSEUR_H

#include <QDialog>

namespace Ui {
class ajouter_fournisseur;
}

class ajouter_fournisseur : public QDialog
{
    Q_OBJECT

public:
    explicit ajouter_fournisseur(QWidget *parent = nullptr);
    ~ajouter_fournisseur();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ajouter_fournisseur *ui;
};

#endif // AJOUTER_FOURNISSEUR_H
