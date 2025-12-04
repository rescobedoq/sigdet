#ifndef DONACION_H
#define DONACION_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Donacion; }
QT_END_NAMESPACE

class Donacion : public QMainWindow
{
    Q_OBJECT

public:
    explicit Donacion(QWidget *parent = nullptr);
    ~Donacion();

private:
    Ui::Donacion *ui;
};

#endif // DONACION_H
