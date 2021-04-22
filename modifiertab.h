#ifndef MODIFIERTAB_H
#define MODIFIERTAB_H

#include <QDialog>

namespace Ui {
class modifiertab;
}

class modifiertab : public QDialog
{
    Q_OBJECT

public:
    explicit modifiertab(QWidget *parent = nullptr);
    ~modifiertab();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::modifiertab *ui;
};

#endif // MODIFIERTAB_H
