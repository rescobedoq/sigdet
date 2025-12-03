#include "donacionesenviadasView.h"
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
#include "conexiondbhelperController.h"
#include "registromodalView.h"

DonacionesEnviadasView::DonacionesEnviadasView(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("DonacionesEnviadasView");

    // --- Layout principal ---
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(24, 24, 24, 24);
    mainLayout->setSpacing(20);

    // --- Header ---
    auto *header = new QHBoxLayout;
    auto *title = new QLabel("Donaciones Enviadas");
    title->setStyleSheet("font-size:28px; font-weight:700; color:#1e293b;");
    auto *btnRegistrar = new QPushButton("Registrar Envio");
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
        auto *modal = new RegistroModal("donaciones_enviadas", this);
        modal->exec();

        // Si se cierra con éxito, refresca la tabla
        QJsonArray data = DonacionesEnviadasView::getDonancionesEnviadas();
        delete mainLayout->takeAt(mainLayout->count() - 1)->widget();
        mainLayout->addWidget(crearTablaDonaciones(data));

        // 🔄 Refrescar Resumen Cards
        reloadResumenCards();
        modal->deleteLater();
    });

    header->addWidget(title);
    header->addStretch();
    header->addWidget(btnRegistrar);
    mainLayout->addLayout(header);


    QJsonArray data = DonacionesEnviadasView::getDonancionesEnviadas();
    // --- Sección de resumen (tarjetas) ---
    resumenCards = crearResumenCards(data);
    mainLayout->addWidget(resumenCards);

    // --- Tabla de donaciones ---
    mainLayout->addWidget(crearTablaDonaciones(data));
}

void DonacionesEnviadasView::reloadResumenCards()
{
    QJsonArray data = getDonancionesEnviadas();

    if (resumenCards) {
        mainLayout->removeWidget(resumenCards);
        delete resumenCards;
        resumenCards = nullptr;
    }

    resumenCards = crearResumenCards(data);
    // 👇 Insertar las cards justo después del header (índice 1)
    mainLayout->insertWidget(1, resumenCards);
}


QJsonArray DonacionesEnviadasView::getDonancionesEnviadas()
{
    DatabaseManager db;
    QString queryStr = R"(
        SELECT
            id,
            beneficiario_id,
            descripcion,
            cantidad,
            unidad,
            estado,
            TO_CHAR(fecha_envio, 'YYYY-MM-DD') AS fecha_envio
        FROM donaciones_enviadas
        ORDER BY cantidad;
    )";

    return db.doGet(queryStr);
}


QWidget* DonacionesEnviadasView::crearResumenCards(const QJsonArray &data) {
    auto *container = new QWidget;
    auto *layout = new QHBoxLayout(container);
    layout->setSpacing(16);
    layout->setContentsMargins(0, 0, 0, 0);

    // 🔹 Calcular estadísticas dinámicamente
    int totalCantidad = 0;
    int enTransito = 0;
    int entregadosHoy = 0;

    QString hoy = QDate::currentDate().toString("yyyy-MM-dd");

    for (const QJsonValue &val : data) {
        QJsonObject obj = val.toObject();

        totalCantidad += obj["cantidad"].toInt();

        QString estado = obj["estado"].toString().toLower();
        if (estado == "transito")
            enTransito++;

        QString fecha = obj["fecha_envio"].toString().left(10);
        if (fecha == hoy)
            entregadosHoy++;
    }

    // 🔹 Función para formatear números grandes (ej: 1,250)
    auto formatNumber = [](int n) {
        return QLocale(QLocale::Spanish).toString(n);
    };

    // 🔹 Función para crear una card visual
    auto crearCard = [](const QString &icon, const QString &titulo, const QString &valor, const QString &desc, const QString &color){
        QFrame *card = new QFrame;
        card->setStyleSheet(R"(
            QFrame {
                background: white;
                border-radius: 12px;
                border: 1px solid #e5e7eb;
                padding: 10px;
            }
        )");

        QVBoxLayout *v = new QVBoxLayout(card);
        v->setContentsMargins(0, 0, 0, 0);
        v->setSpacing(1);

        QHBoxLayout *h = new QHBoxLayout;
        h->setContentsMargins(0, 0, 0, 0);
        h->setSpacing(1);
        h->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        QLabel *iconLbl = new QLabel;
        iconLbl->setPixmap(QIcon(icon).pixmap(30,30));
        iconLbl->setFixedSize(50, 50);
        iconLbl->setStyleSheet("background: transparent; border: none;");

        QLabel *text = new QLabel(titulo);
        text->setStyleSheet("font-size:13px; color:#475569; background: transparent; border: none;");

        h->addWidget(iconLbl);
        h->addWidget(text);
        h->addStretch();
        v->addLayout(h);

        QLabel *num = new QLabel(valor);
        num->setAlignment(Qt::AlignLeft);
        num->setStyleSheet("font-size:40px; font-weight:700; color:#0f172a; background: transparent; border: none;");
        v->addWidget(num);

        QLabel *sub = new QLabel(desc);
        sub->setAlignment(Qt::AlignLeft);
        sub->setStyleSheet("font-size:12px; color:#64748b; background: transparent; border: none;");
        v->addWidget(sub);

        return card;
    };

    // 🔹 Crear las cards con datos reales
    layout->addWidget(crearCard(":/icons/donacionesEnviadasIcons/local_shipping.svg",
                                "Total Envíos Realizados",
                                formatNumber(totalCantidad),
                                "Desde el inicio de operaciones", "#2563eb"));

    layout->addWidget(crearCard(":/icons/donacionesEnviadasIcons/route.svg",
                                "Envíos en Tránsito",
                                QString::number(enTransito),
                                "Con entrega programada pronto", "#facc15"));

    layout->addWidget(crearCard(":/icons/donacionesEnviadasIcons/check_circle.svg",
                                "Envíos Entregados Hoy",
                                QString::number(entregadosHoy),
                                "Actualizado hace unos minutos", "#22c55e"));

    return container;
}

QWidget* DonacionesEnviadasView::crearTablaDonaciones(const QJsonArray &data) {
    QStringList headers = {
        "beneficiario_id",
        "descripcion",
        "cantidad",
        "unidad",
        "estado",
        "fecha_envio",
    };

    qDebug().noquote() << QJsonDocument(data).toJson(QJsonDocument::Indented);
    auto *tablaWidget = new TableWidgetCard("Detalle de Donaciones Enviadas", data, "beneficiario_id", this,headers);

    // ✅ Conecta la lógica de eliminar y actualizar desde la clase helper
    ConexionDBHelper::conexionDBEliminar(
        this,
        tablaWidget,
        headers,
        "donaciones_enviadas",
        [this]() {
            reloadResumenCards(); // 👈 también recarga las cards
            return getDonancionesEnviadas();
        }
        );

    ConexionDBHelper::conexionDBActualizar(
        this,
        tablaWidget,
        headers,
        "donaciones_enviadas",
        [this]() {
            reloadResumenCards(); // 👈 también recarga las cards
            return getDonancionesEnviadas();
        }
        );
    return tablaWidget;
}
