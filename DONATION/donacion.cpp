#include "donacion.h"
#include "ui_donacion.h"
#include <QMessageBox> // Para mostrar alertas

Donacion::Donacion(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Donacion)
{
    ui->setupUi(this);

    // --- CONFIGURACIÓN DE LA TABLA ---
    ui->tablaDonaciones->setColumnCount(3); // 3 Columnas
    QStringList encabezados;
    encabezados << "Donante" << "Producto" << "Cantidad";
    ui->tablaDonaciones->setHorizontalHeaderLabels(encabezados);

    // Hacer que las columnas ocupen todo el ancho
    ui->tablaDonaciones->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

Donacion::~Donacion()
{
    delete ui;
}

// LÓGICA DEL BOTÓN REGISTRAR
void Donacion::on_btnRegistrar_clicked()
{
    // 1. Obtener texto de las cajas
    QString nombre = ui->txtDonante->text();
    QString producto = ui->txtProducto->text();
    int cantidad = ui->spinCantidad->value();

    // 2. Validar que no estén vacíos
    if(nombre.isEmpty() || producto.isEmpty() || cantidad <= 0) {
        QMessageBox::warning(this, "Error", "Por favor llene todos los datos y la cantidad debe ser mayor a 0.");
        return; // Salir de la función si hay error
    }

    // 3. Insertar fila en la tabla
    int filaActual = ui->tablaDonaciones->rowCount();
    ui->tablaDonaciones->insertRow(filaActual);

    // 4. Poner los datos en las celdas
    ui->tablaDonaciones->setItem(filaActual, 0, new QTableWidgetItem(nombre));
    ui->tablaDonaciones->setItem(filaActual, 1, new QTableWidgetItem(producto));
    ui->tablaDonaciones->setItem(filaActual, 2, new QTableWidgetItem(QString::number(cantidad)));

    // 5. Avisar y limpiar
    QMessageBox::information(this, "Éxito", "Donación registrada correctamente.");
    limpiarFormulario();
}

void Donacion::limpiarFormulario()
{
    ui->txtDonante->clear();
    ui->txtProducto->clear();
    ui->spinCantidad->setValue(0);
    ui->txtDonante->setFocus(); // Pone el cursor en el primer campo
}
