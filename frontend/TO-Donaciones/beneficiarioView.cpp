#include "beneficiarioView.h"
#include "tablewidgetcardView.h"
#include "databasemanagerController.h"

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
#include "conexiondbhelperController.h"
#include "registromodalView.h"

BeneficiarioView::BeneficiarioView(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("DonacionesRecibidasView");

    // --- Layout principal ---
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(24, 24, 24, 24);
    mainLayout->setSpacing(20);

    // --- Header ---
    auto *header = new QHBoxLayout;
    auto *title = new QLabel("Beneficiarios");
    title->setStyleSheet("font-size:28px; font-weight:700; color:#1e293b;");
    auto *btnRegistrar = new QPushButton("Registrar Beneficiario");
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
        auto *modal = new RegistroModal("beneficiarios", this);
        modal->exec();

        // Si se cierra con éxito, refresca la tabla
        delete mainLayout->takeAt(mainLayout->count() - 1)->widget();
        mainLayout->addWidget(crearTablaBeneficiaros());
    });

    header->addWidget(title);
    header->addStretch();
    header->addWidget(btnRegistrar);
    mainLayout->addLayout(header);

    // --- Tabla de donaciones ---
    mainLayout->addWidget(crearTablaBeneficiaros());
}

QJsonArray BeneficiarioView::getBeneficiarios()
{
    DatabaseManager db;
    QString queryStr = R"(
        SELECT id, nombre, apellido, referencia, direccion, telefono, TO_CHAR(created_at, 'YYYY-MM-DD') AS fecha_creacion
        FROM beneficiarios
        ORDER BY nombre;
    )";

    return db.doGet(queryStr);
}

QWidget* BeneficiarioView::crearTablaBeneficiaros() {

    QJsonArray data = BeneficiarioView::getBeneficiarios();

    QStringList headers = {
        "nombre",
        "apellido",
        "referencia",
        "direccion",
        "telefono",
        "fecha_creacion"
    };

    qDebug().noquote() << QJsonDocument(data).toJson(QJsonDocument::Indented);
    auto *tablaWidget = new TableWidgetCard("Lista de Beneficiarios", data, "referencia", this,headers);

    // ✅ Conecta la lógica de eliminar y actualizar desde la clase helper
    ConexionDBHelper::conexionDBEliminar(this, tablaWidget, headers, "beneficiarios", [this]() { return getBeneficiarios(); });
    ConexionDBHelper::conexionDBActualizar(this, tablaWidget, headers, "beneficiarios", [this]() { return getBeneficiarios(); });

    return tablaWidget;
}
