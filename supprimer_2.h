#ifndef SUPPRIMER_2_H
#define SUPPRIMER_2_H

#include <QDialog>

namespace Ui {
class supprimer_2;
}

class supprimer_2 : public QDialog
{
    Q_OBJECT

public:
    explicit supprimer_2(QWidget *parent = nullptr);
    ~supprimer_2();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::supprimer_2 *ui;

};

#endif // SUPPRIMER_2_H
