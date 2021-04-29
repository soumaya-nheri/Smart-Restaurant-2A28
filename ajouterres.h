#ifndef AJOUTERRES_H
#define AJOUTERRES_H

#include <QDialog>

namespace Ui {
class ajouterres;
}

class ajouterres : public QDialog
{
    Q_OBJECT

public:
    explicit ajouterres(QWidget *parent = nullptr);
    ~ajouterres();

private slots:
    void on_buttonBox_accepted();



private:
    Ui::ajouterres *ui;
};

#endif // AJOUTERRES_H
