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
    Donacion(QWidget *parent = nullptr);
    ~Donacion();

private slots:
    // Esta función reacciona al clic del botón
    void on_btnRegistrar_clicked();

private:
    Ui::Donacion *ui;

    // Función auxiliar para limpiar las cajas de texto
    void limpiarFormulario();
};
#endif // DONACION_H
