#ifndef DONACION_H
#define DONACION_H

#include <QMainWindow>
#include "controlador.h" // Incluimos el controlador

QT_BEGIN_NAMESPACE
namespace Ui { class Donacion; }
QT_END_NAMESPACE

class Donacion : public QMainWindow
{
    Q_OBJECT

public:
    Donacion(QWidget *parent = nullptr);
    ~Donacion();

private slots:
    void on_btnRegistrar_clicked();

private:
    Ui::Donacion *ui;

    // Instancia del controlador (Composición)
    ControladorDonaciones controlador;

    void limpiarFormulario();
    void configurarTabla();
};
#endif // DONACION_H
