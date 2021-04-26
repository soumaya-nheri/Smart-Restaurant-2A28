#ifndef STATISTIQUE_H
#define STATISTIQUE_H

#include <QWidget>

namespace Ui {
class Statistique;
}

class Statistique : public QWidget
{
    Q_OBJECT

public:
    explicit Statistique(QWidget *parent = nullptr);
    ~Statistique();
    void make();
private:
    Ui::Statistique *ui;
};

#endif // STATISTIQUE_H
