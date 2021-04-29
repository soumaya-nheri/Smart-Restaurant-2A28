#ifndef MODIFIERRES_H
#define MODIFIERRES_H

#include <QDialog>

namespace Ui {
class modifierres;
}

class modifierres : public QDialog
{
    Q_OBJECT

public:
    explicit modifierres(QWidget *parent = nullptr);
    ~modifierres();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::modifierres *ui;
};

#endif // MODIFIERRES_H
