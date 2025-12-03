#include "donantesView.h"
#include "tablewidgetcardView.h"
#include <QHeaderView>
#include <QSpacerItem>
#include <QSizePolicy>
#include <QIcon>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include "databasemanagerController.h"
#include <QMessageBox>
#include "conexiondbhelperController.h"
#include "registromodalView.h"

DonantesView::DonantesView(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("DonacionesRecibidasView");

    // --- Layout principal ---
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(24, 24, 24, 24);
    mainLayout->setSpacing(20);

    // --- Header ---
    auto *header = new QHBoxLayout;
    auto *title = new QLabel("Donantes");
    title->setStyleSheet("font-size:28px; font-weight:700; color:#1e293b;");
    auto *btnRegistrar = new QPushButton("Registrar Donante");
    btnRegistrar->setIcon(QIcon(":/icons/generalIcons/add_circle.svg"));
    btnRegistrar->setStyleSheet(R"(
        QPushButton {
            background-color: #2563eb;
            color: white;
            font-weight:600;
            border:none;
            border-radius:8px;
            padding:8px 16px;
        }
        QPushButton:hover {
            background-color:#1d4ed8;
        }
    )");

    connect(btnRegistrar, &QPushButton::clicked, this, [this]() {
        auto *modal = new RegistroModal("donantes", this);
        modal->exec();

        // Si se cierra con éxito, refresca la tabla
        delete mainLayout->takeAt(mainLayout->count() - 1)->widget();
        mainLayout->addWidget(crearTablaDonantes());
    });

    header->addWidget(title);
    header->addStretch();
    header->addWidget(btnRegistrar);
    mainLayout->addLayout(header);

    // --- Tabla de donaciones ---
    mainLayout->addWidget(crearTablaDonantes());
}

QJsonArray DonantesView::getDonantes()
{
    DatabaseManager db;
    QString queryStr = R"(
        SELECT
            id,
            nombre,
            apellido,
            telefono,
            direccion,
            tipo_documento,
            numero_documento,
            TO_CHAR(created_at, 'YYYY-MM-DD') AS fecha_creacion
        FROM donantes
        ORDER BY nombre;
    )";

    return db.doGet(queryStr);
}

QWidget* DonantesView::crearTablaDonantes() {

    // Obtener sólo las columnas requeridas del beneficiario
    QJsonArray data = DonantesView::getDonantes();

    QStringList headers = {
        "nombre",
        "apellido",
        "telefono",
        "direccion",
        "tipo_documento",
        "numero_documento",
        "fecha_creacion",
    };

    qDebug().noquote() << QJsonDocument(data).toJson(QJsonDocument::Indented);
    auto *tablaWidget = new TableWidgetCard("Lista de Donantes", data, "tipo_documento", this,headers);

    // ✅ Conecta la lógica de eliminar y actualizar desde la clase helper
    ConexionDBHelper::conexionDBEliminar(this, tablaWidget, headers, "donantes", [this]() { return getDonantes(); });
    ConexionDBHelper::conexionDBActualizar(this, tablaWidget, headers, "donantes", [this]() { return getDonantes(); });

    return tablaWidget;
}
