#ifndef SUPPRIMERTAB_H
#define SUPPRIMERTAB_H

#include <QDialog>

namespace Ui {
class supprimertab;
}

class supprimertab : public QDialog
{
    Q_OBJECT

public:
    explicit supprimertab(QWidget *parent = nullptr);
    ~supprimertab();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::supprimertab *ui;

};

#endif // SUPPRIMERTAB_H
