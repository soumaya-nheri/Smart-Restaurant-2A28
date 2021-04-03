#ifndef AJOUTER_2_H
#define AJOUTER_2_H

#include <QDialog>

namespace Ui {
class ajouter_2;
}

class ajouter_2 : public QDialog
{
    Q_OBJECT

public:
    explicit ajouter_2(QWidget *parent = nullptr);
    ~ajouter_2();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ajouter_2 *ui;
};

#endif // AJOUTER_2_H
