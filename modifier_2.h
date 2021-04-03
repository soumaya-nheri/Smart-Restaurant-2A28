#ifndef MODIFIER_2_H
#define MODIFIER_2_H

#include <QDialog>

namespace Ui {
class modifier_2;
}

class modifier_2 : public QDialog
{
    Q_OBJECT

public:
    explicit modifier_2(QWidget *parent = nullptr);
    ~modifier_2();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::modifier_2 *ui;
};

#endif // MODIFIER_2_H
