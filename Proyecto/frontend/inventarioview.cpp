#include "inventarioView.h"
#include "tablewidgetcardView.h"
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include "databasemanagerController.h"
#include "conexiondbhelperController.h"
#include "registromodalView.h"
InventarioView::InventarioView(QWidget *parent)
    : QWidget(parent)
{
    // Estilos generales y layout
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(24, 20, 24, 20);
    mainLayout->setSpacing(16);
    setStyleSheet(R"(
        QWidget#card {
            background-color: white;
            border: 1px solid #e5e7eb;
            border-radius: 12px;
        }
        QLabel.title {
            font-size: 20px;
            font-weight: 700;
            color: #111318;
        }
        QLabel.subtitle {
            font-size: 13px;
            color: #616f89;
        }
        QPushButton.primary {
            background-color: #2563eb;
            color: white;
            font-weight: 700;
            border-radius: 8px;
            padding: 6px 12px;
        }
        QPushButton.icon {
            background: transparent;
            border: none;
        }
        QLineEdit.search {
            background-color: #f3f4f6;
            border: 1px solid #e5e7eb;
            border-radius: 8px;
            padding-left: 36px;
            height: 36px;
        }
    )");



    // Obtener sólo las columnas requeridas del beneficiario
    QJsonArray data = InventarioView::getInventario();


    setupHeader(mainLayout);
    setupChartCard(mainLayout,data);
    setupTableCard(mainLayout,data);

}

/* ------------------------
   UI Setup helpers
   ------------------------ */
QJsonArray InventarioView::getInventario()
{
    DatabaseManager db;
    QString queryStr = R"(
        SELECT
            i.id,
            i.tipo_id,
            t.codigo AS cod_tipo,
            i.descripcion,
            i.cantidad,
            i.unidad,
            i.ubicacion,
            i.estado,
            TO_CHAR(i.created_at, 'YYYY-MM-DD') AS fecha_creacion
        FROM inventario i LEFT JOIN tipos_donacion t ON i.tipo_id = t.id
        ORDER BY i.cantidad;
    )";
    return db.doGet(queryStr);
}

void InventarioView::setupHeader(QVBoxLayout *mainLayout)
{
    auto *headerLayout = new QHBoxLayout;
    headerLayout->setSpacing(12);

    auto *titleBox = new QVBoxLayout;
    auto *title = new QLabel("Gestión de Inventario");
    title->setObjectName("title");
    title->setProperty("class", "title");
    title->setStyleSheet("font-size:22px; font-weight:700; color: #111318;");
    auto *subtitle = new QLabel("Visualiza y administra los ítems donados.");
    subtitle->setObjectName("subtitle");
    subtitle->setProperty("class", "subtitle");
    subtitle->setStyleSheet("font-size:13px; color:#616f89;");

    titleBox->addWidget(title);
    titleBox->addWidget(subtitle);

    auto *addBtn = new QPushButton;
    addBtn->setObjectName("addBtn");
    addBtn->setProperty("class", "primary");
    addBtn->setText("Añadir Ítem");
    addBtn->setFixedHeight(36);
    addBtn->setCursor(Qt::PointingHandCursor);
    // ícono material add_circle (SVG en resources.qrc)
    addBtn->setIcon(QIcon(":/icons/generalIcons/add_circle.svg"));
    addBtn->setIconSize(QSize(18,18));
    addBtn->setStyleSheet("QPushButton { padding-left:10px; padding-right:12px; }");

    connect(addBtn, &QPushButton::clicked, this, [this]() {
        auto *modal = new RegistroModal("inventario", this);
        modal->exec();

        // Si se cierra con éxito, refresca la tabla
        // 🔄 Refrescar la tabla
        tablaWidget->reloadData(getInventario(), {
                                                     "tipo_id",
                                                     "descripcion",
                                                     "cantidad",
                                                     "unidad",
                                                     "ubicacion",
                                                     "estado",
                                                     "fecha_creacion"
                                                 });

        // 🔄 Refrescar el gráfico
        reloadChart();
        modal->deleteLater();
    });

    headerLayout->addLayout(titleBox);
    headerLayout->addStretch();
    headerLayout->addWidget(addBtn);

    mainLayout->addLayout(headerLayout);
}

/* Chart card: visual bar-like indicators using QProgressBar */
void InventarioView::setupChartCard(QVBoxLayout *mainLayout, const QJsonArray &data)
{
    chartCard = new QFrame;
    chartCard->setObjectName("card");
    chartCard->setProperty("class", "card");
    chartCard->setStyleSheet(R"(
        QFrame#card {
            background-color: white;
            border: 1px solid #e5e7eb;
            border-radius:12px;
            padding: 14px;
        }
    )");

    auto *v = new QVBoxLayout(chartCard);
    v->setSpacing(10);

    // --- Encabezado ---
    auto *topRow = new QHBoxLayout;
    auto *title = new QLabel("Distribución de Donaciones por Tipo");
    title->setStyleSheet("font-size:16px; font-weight:600; color:#111318;");

    // Total de items
    int total = 0;
    for (const QJsonValue &val : data)
        total += val.toObject().value("cantidad").toInt();

    auto *meta = new QLabel(QString("%1 Items").arg(total));
    meta->setStyleSheet("font-size:18px; font-weight:700; color:#111318;");

    topRow->addWidget(title);
    topRow->addStretch();
    v->addLayout(topRow);
    v->addWidget(meta);

    // --- Contenedor con scroll ---
    auto *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setStyleSheet(R"(background-color: white;)");
    // --- Widget interno ---
    QWidget *container = new QWidget;
    auto *barsLayout = new QVBoxLayout(container);
    barsLayout->setSpacing(8);
    barsLayout->setContentsMargins(0, 0, 0, 0);

    // Calcular máximo
    int maxCantidad = 0;
    for (const QJsonValue &val : data)
        maxCantidad = std::max(maxCantidad, val.toObject().value("cantidad").toInt());
    if (maxCantidad == 0) maxCantidad = 1;

    // Crear filas
    for (const QJsonValue &val : data) {
        QJsonObject obj = val.toObject();
        QString tipo = obj.value("cod_tipo").toString();
        int cantidad = obj.value("cantidad").toInt();

        auto *row = new QHBoxLayout;
        QLabel *lbl = new QLabel(tipo);
        lbl->setFixedWidth(90);
        lbl->setStyleSheet("color:#616f89; font-weight:600;");

        QProgressBar *bar = new QProgressBar;
        bar->setRange(0, 100);
        int porcentaje = static_cast<int>((cantidad * 100.0) / maxCantidad);
        bar->setValue(porcentaje);
        bar->setTextVisible(false);
        bar->setFixedHeight(12);
        bar->setStyleSheet(R"(
            QProgressBar { border-radius:6px; background: #f3f4f6; }
            QProgressBar::chunk { background: #2563eb; border-radius:6px; }
        )");

        row->addWidget(lbl);
        row->addWidget(bar, /*stretch*/ 1);
        barsLayout->addLayout(row);
    }

    container->setLayout(barsLayout);
    scrollArea->setWidget(container);

    // --- Altura máxima visible (7 filas aprox) ---
    int rowHeight = 26; // altura estimada por fila
    int maxVisible = 7;
    scrollArea->setFixedHeight(rowHeight * maxVisible);

    v->addWidget(scrollArea);
    mainLayout->addWidget(chartCard);
}
void InventarioView::reloadChart()
{
    QJsonArray updatedData = getInventario();

    // Buscar el índice actual del chartCard en el layout
    int index = -1;
    for (int i = 0; i < mainLayout->count(); ++i) {
        if (mainLayout->itemAt(i)->widget() == chartCard) {
            index = i;
            break;
        }
    }

    // Eliminar el chart actual del layout
    if (chartCard) {
        mainLayout->removeWidget(chartCard);
        delete chartCard;
        chartCard = nullptr;
    }

    // Crear el nuevo chart
    chartCard = new QFrame;
    setupChartCardAt(index, updatedData); // 👈 la nueva función auxiliar
}
void InventarioView::setupChartCardAt(int insertIndex, const QJsonArray &data)
{
    chartCard = new QFrame;
    chartCard->setObjectName("card");
    chartCard->setProperty("class", "card");
    chartCard->setStyleSheet(R"(
        QFrame#card {
            background-color: white;
            border: 1px solid #e5e7eb;
            border-radius:12px;
            padding: 14px;
        }
    )");

    auto *v = new QVBoxLayout(chartCard);
    v->setSpacing(10);

    // --- Encabezado ---
    auto *topRow = new QHBoxLayout;
    auto *title = new QLabel("Distribución de Donaciones por Tipo");
    title->setStyleSheet("font-size:16px; font-weight:600; color:#111318;");

    int total = 0;
    for (const QJsonValue &val : data)
        total += val.toObject().value("cantidad").toInt();

    auto *meta = new QLabel(QString("%1 Items").arg(total));
    meta->setStyleSheet("font-size:18px; font-weight:700; color:#111318;");

    topRow->addWidget(title);
    topRow->addStretch();
    v->addLayout(topRow);
    v->addWidget(meta);

    // --- Barras ---
    // --- Contenedor con scroll ---
    auto *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setStyleSheet(R"(background-color: white;)");


    // --- Widget interno ---

    QWidget *container = new QWidget;
    auto *barsLayout = new QVBoxLayout(container);

    int maxCantidad = 0;
    for (const QJsonValue &val : data)
        maxCantidad = std::max(maxCantidad, val.toObject().value("cantidad").toInt());
    if (maxCantidad == 0) maxCantidad = 1;

    for (const QJsonValue &val : data) {
        QJsonObject obj = val.toObject();
        QString tipo = obj.value("cod_tipo").toString();
        int cantidad = obj.value("cantidad").toInt();

        auto *row = new QHBoxLayout;
        QLabel *lbl = new QLabel(tipo);
        lbl->setFixedWidth(90);
        lbl->setStyleSheet("color:#616f89; font-weight:600;");

        QProgressBar *bar = new QProgressBar;
        bar->setRange(0, 100);
        bar->setValue(static_cast<int>((cantidad * 100.0) / maxCantidad));
        bar->setTextVisible(false);
        bar->setFixedHeight(12);
        bar->setStyleSheet(R"(
            QProgressBar { border-radius:6px; background: #f3f4f6; }
            QProgressBar::chunk { background: #2563eb; border-radius:6px; }
        )");

        row->addWidget(lbl);
        row->addWidget(bar, 1);
        barsLayout->addLayout(row);
    }

    container->setLayout(barsLayout);
    scrollArea->setWidget(container);
    v->addWidget(scrollArea);

    // 🔹 Insertar el nuevo chart en la posición original
    if (insertIndex >= 0 && insertIndex <= mainLayout->count())
        mainLayout->insertWidget(insertIndex, chartCard);
    else
        mainLayout->addWidget(chartCard);
}
/* Table card */
void InventarioView::setupTableCard(QVBoxLayout *mainLayout, const QJsonArray &data)
{
    QStringList headers = {
        "id",
        "descripcion",
        "cantidad",
        "unidad",
        "ubicacion",
        "estado",
        "fecha_creacion",
    };

    qDebug().noquote() << QJsonDocument(data).toJson(QJsonDocument::Indented);
    tablaWidget = new TableWidgetCard("Inventario Actualmente", data, "unidad", this, headers);

    // ✅ Conecta la lógica de eliminar y actualizar desde la clase helper
    ConexionDBHelper::conexionDBEliminar(this, tablaWidget, headers, "inventario", [this]() { return getInventario(); });
    ConexionDBHelper::conexionDBActualizar(this, tablaWidget, headers, "inventario", [this]() { return getInventario(); });
    // ✅ Conexión adicional SOLO para refrescar el gráfico

    connect(tablaWidget, &TableWidgetCard::actionTriggered, this, [this](const QString &, const QString &action) {
        if (action == "eliminar") {
            reloadChart();
        }
    });

    connect(tablaWidget, &TableWidgetCard::actionTriggeredWithData, this,
        [this](const QString &, const QString &action, const QJsonObject &) {
            if (action == "confirmar") {
                reloadChart();
            }
        });
    mainLayout -> addWidget(tablaWidget);
}
