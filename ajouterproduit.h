#ifndef AJOUTER_H
#define AJOUTER_H

#include <QDialog>

namespace Ui {
class ajouterproduit;
}

class ajouterproduit : public QDialog
{
    Q_OBJECT

public:
    explicit ajouterproduit(QWidget *parent = nullptr);
    ~ajouterproduit();

private slots:
    void on_buttonBox_accepted();



private:
    Ui::ajouterproduit *ui;
};

#endif // AJOUTER_H
