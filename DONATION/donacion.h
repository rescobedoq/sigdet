#ifndef DONACION_H
#define DONACION_H

#include <QWidget>

namespace Ui {
class Donacion;
}

class Donacion : public QWidget
{
    Q_OBJECT

public:
    explicit Donacion(QWidget *parent = nullptr);
    ~Donacion();

private:
    Ui::Donacion *ui;
};

#endif // DONACION_H
