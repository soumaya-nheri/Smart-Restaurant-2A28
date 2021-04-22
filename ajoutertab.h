#ifndef AJOUTERTAB_H
#define AJOUTERTAB_H

#include <QDialog>

namespace Ui {
class ajoutertab;
}

class ajoutertab : public QDialog
{
    Q_OBJECT

public:
    explicit ajoutertab(QWidget *parent = nullptr);
    ~ajoutertab();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ajoutertab *ui;
};

#endif // AJOUTERTAB_H
