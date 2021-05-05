#ifndef MODIFIER_FOURNISSEUR_H
#define MODIFIER_FOURNISSEUR_H

#include <QDialog>

namespace Ui {
class modifier_fournisseur;
}

class modifier_fournisseur  : public QDialog
{
    Q_OBJECT

public:
    explicit modifier_fournisseur(QWidget *parent = nullptr);
    ~modifier_fournisseur();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::modifier_fournisseur *ui;
};

#endif // MODIFIER_FOURNISSEUR_H
