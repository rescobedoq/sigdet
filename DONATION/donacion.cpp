#include "donacion.h"
#include "ui_donacion.h"
#include <QMessageBox>

Donacion::Donacion(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Donacion)
{
    ui->setupUi(this);
    configurarTabla();
}

Donacion::~Donacion()
{
    delete ui;
}

void Donacion::configurarTabla() {
    ui->tablaDonaciones->setColumnCount(4); // Agregamos columna "Tipo"
    QStringList encabezados;
    encabezados << "Tipo" << "Donante" << "Producto" << "Cantidad";
    ui->tablaDonaciones->setHorizontalHeaderLabels(encabezados);
    ui->tablaDonaciones->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void Donacion::on_btnRegistrar_clicked()
{
    // 1. Obtener datos
    QString nombre = ui->txtDonante->text();
    QString producto = ui->txtProducto->text();
    int cantidad = ui->spinCantidad->value();

    // Lógica básica de UI: determinar el tipo (puedes agregar un RadioButton en el UI para esto)
    // Por ahora, asumiremos que si el producto contiene "camisa" o "pantalon" es ropa.
    bool esRopa = producto.contains("camisa", Qt::CaseInsensitive) ||
                  producto.contains("pantalon", Qt::CaseInsensitive);

    // 2. Validación simple en UI
    if(nombre.isEmpty() || producto.isEmpty() || cantidad <= 0) {
        QMessageBox::warning(this, "Error", "Datos inválidos.");
        return;
    }

    try {
        // 3. Delegar al CONTROLADOR (MVC)
        controlador.registrarDonacion(nombre, producto, cantidad, esRopa);

        // 4. Actualizar Tabla (La vista reacciona)
        int fila = ui->tablaDonaciones->rowCount();
        ui->tablaDonaciones->insertRow(fila);

        QString tipoStr = esRopa ? "Ropa" : "Alimento";

        ui->tablaDonaciones->setItem(fila, 0, new QTableWidgetItem(tipoStr));
        ui->tablaDonaciones->setItem(fila, 1, new QTableWidgetItem(nombre));
        ui->tablaDonaciones->setItem(fila, 2, new QTableWidgetItem(producto));
        ui->tablaDonaciones->setItem(fila, 3, new QTableWidgetItem(QString::number(cantidad)));

        // 5. Uso de Multithreading (Llamada asíncrona)
        controlador.guardarEnBaseDeDatosAsync();

        QMessageBox::information(this, "Éxito", "Donación registrada y guardando en segundo plano.");
        limpiarFormulario();

    } catch (const std::exception &e) {
        // Manejo de errores que vienen del modelo/controlador
        QMessageBox::critical(this, "Error Crítico", e.what());
    }
}

void Donacion::limpiarFormulario()
{
    // Uso de Lambdas para tareas pequeñas (Programación Moderna)
    auto limpiar = [this]() {
        ui->txtDonante->clear();
        ui->txtProducto->clear();
        ui->spinCantidad->setValue(0);
        ui->txtDonante->setFocus();
    };

    limpiar();
}
