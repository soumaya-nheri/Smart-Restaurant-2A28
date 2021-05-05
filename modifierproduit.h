#ifndef MODIFIER_H
#define MODIFIER_H

#include <QDialog>

namespace Ui {
class modifierproduit;
}

class modifierproduit : public QDialog
{
    Q_OBJECT

public:
    explicit modifierproduit(QWidget *parent = nullptr);
    ~modifierproduit();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::modifierproduit *ui;
};

#endif // MODIFIER_H
