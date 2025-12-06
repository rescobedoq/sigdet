#include "informesView.h"
#include "databasemanagerController.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QFrame>
#include <QGridLayout>
#include <QJsonDocument>
#include <QJsonValue>
#include <QDateTime>
#include <QMap>
#include <algorithm>
#include <QDebug>
// Qt Charts
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QRandomGenerator>
#include <QGraphicsLayout>

#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QDate>
#include <QMessageBox>

InformesView::InformesView(QWidget *parent)
    : QWidget(parent)
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(24, 24, 24, 24);
    mainLayout->setSpacing(24);

    mainLayout->addWidget(createHeader());
    mainLayout->addWidget(createFiltros());
    mainLayout->addWidget(createKpiGrid());
    mainLayout->addWidget(createGraficos());
    //
    // ---------------- DATOS REALES DESDE LA BD ----------------
    //
    DatabaseManager db;

    // --- Donaciones Recibidas ---
    QJsonArray recibidas = db.doGet(R"(
        SELECT
            dr.fecha_donacion AS date,
            dr.cantidad AS amount,
            td.descripcion AS category,
            CONCAT(d.nombre, ' ', COALESCE(d.apellido, '')) AS donorName
        FROM donaciones_recibidas dr
        LEFT JOIN donantes d ON dr.donante_id = d.id
        LEFT JOIN inventario i ON dr.inventario_id = i.id
        LEFT JOIN tipos_donacion td ON i.tipo_id = td.id
        ORDER BY dr.fecha_donacion DESC
        LIMIT 15
    )");
        setDonacionesRecibidas(recibidas);

        // --- Donaciones Enviadas ---
    QJsonArray enviadas = db.doGet(R"(
        SELECT
            de.fecha_envio AS date,
            de.cantidad AS amount
        FROM donaciones_enviadas de
        ORDER BY de.fecha_envio DESC
        LIMIT 15
    )");
        setDonacionesEnviadas(enviadas);

        // --- Inventario ---
    QJsonArray inventario = db.doGet(R"(
        SELECT
            td.descripcion AS category,
            i.cantidad AS stock
        FROM inventario i
        LEFT JOIN tipos_donacion td ON i.tipo_id = td.id
        LIMIT 15
    )");
        setInventario(inventario);

        // --- Beneficiarios ---
    QJsonArray beneficiarios = db.doGet(R"(
        SELECT
            created_at AS date
        FROM beneficiarios
        ORDER BY created_at DESC
        LIMIT 10
    )");
        setBeneficiarios(beneficiarios);

        // --- Donantes ---
    QJsonArray donantesArr = db.doGet(R"(
        SELECT
            CONCAT(nombre, ' ', COALESCE(apellido, '')) AS donorName,
            COALESCE(SUM(dr.cantidad), 0) AS amount
        FROM donantes d
        LEFT JOIN donaciones_recibidas dr ON dr.donante_id = d.id
        GROUP BY d.id
        ORDER BY amount DESC
        LIMIT 10
    )");
    setDonantes(donantesArr);
}

// ---------------- HEADER ----------------
QWidget* InformesView::createHeader() {
    auto *container = new QWidget;
    auto *layout = new QHBoxLayout(container);
    layout->setContentsMargins(0,0,0,0);

    auto *titulo = new QLabel("KPI y Tendencias de Donaciones");
    titulo->setStyleSheet("font-size: 26px; font-weight: 700; color: #1e293b;");


    layout->addWidget(titulo);
    layout->addStretch();
    return container;
}

QWidget* InformesView::createFiltros() {
    auto *container = new QWidget;
    auto *layout = new QHBoxLayout(container);
    layout->setContentsMargins(16, 16, 16, 16);
    layout->setSpacing(12);

    auto *label = new QLabel("Filtros rápidos:");
    label->setStyleSheet("font-weight: 600; color: #1E293B; font-size: 14px; border:none;");

    QString btnStyle = R"(
        QPushButton {
            background-color: #F1F5F9;
            color: #334155;
            border: none;
            border-radius: 8px;
            padding: 6px 16px;
            font-size: 14px;
            font-weight: 500;
        }
        QPushButton:hover {
            background-color: #E2E8F0;
        }
        QPushButton:pressed {
            background-color: #CBD5E1;
        }
        QPushButton:checked {
            background-color: #2563EB;
            color: white;
        }
    )";

    // --- Botones (toggleables) ---
    auto *btnTodo   = new QPushButton("Todo");
    auto *btn7dias = new QPushButton("Últimos 7 días");
    auto *btnMes   = new QPushButton("Este Mes");
    auto *btnAnio  = new QPushButton("Este Año");

    btnTodo->setCheckable(true);
    btn7dias->setCheckable(true);
    btnMes->setCheckable(true);
    btnAnio->setCheckable(true);

    btnTodo->setStyleSheet(btnStyle);
    btn7dias->setStyleSheet(btnStyle);
    btnMes->setStyleSheet(btnStyle);
    btnAnio->setStyleSheet(btnStyle);

    layout->addWidget(label);
    layout->addWidget(btnTodo);
    layout->addWidget(btn7dias);
    layout->addWidget(btnMes);
    layout->addWidget(btnAnio);
    layout->addStretch();

    container->setStyleSheet("background: white; border-radius: 12px; border: 1px solid #E2E8F0;");

    // --- Lógica del filtro global ---
    auto aplicarFiltro = [this](const QString &modo) {
        QDate hoy = QDate::currentDate();
        QDate desde;

        if (modo == "7dias")
            desde = hoy.addDays(-7);
        else if (modo == "mes")
            desde = QDate(hoy.year(), hoy.month(), 1);
        else if (modo == "anio")
            desde = QDate(hoy.year(), 1, 1);
        else
            desde = QDate(1900, 1, 1); // "Todo"

        auto filtrarPorFecha = [&](const QJsonArray &arr) {
            if (modo == "todo") return arr; // sin filtro
            QJsonArray filtrado;
            for (const auto &v : arr) {
                if (!v.isObject()) continue;
                QJsonObject obj = v.toObject();

                // Si tiene campo "date", aplicar filtro
                if (obj.contains("date")) {
                    QDate d = QDateTime::fromString(obj.value("date").toString(), Qt::ISODate).date();
                    if (d.isValid() && d >= desde && d <= hoy)
                        filtrado.append(obj);
                } else {
                    // Si no tiene fecha, conservar el registro
                    filtrado.append(obj);
                }
            }
            return filtrado;
        };

        // --- Filtrar y actualizar todas las fuentes ---
        QJsonArray rec = filtrarPorFecha(donacionesRecibidasOriginal_);
        QJsonArray env = filtrarPorFecha(donacionesEnviadasOriginal_);
        QJsonArray inv = filtrarPorFecha(inventarioOriginal_);
        QJsonArray dons = filtrarPorFecha(donantesOriginal_);
        QJsonArray ben = filtrarPorFecha(beneficiariosOriginal_);

        // --- Actualizar vistas ---
        setDonacionesRecibidas(rec);
        setDonacionesEnviadas(env);
        setInventario(inv);
        setDonantes(dons);
        setBeneficiarios(ben);
    };

    // --- Conectar señales ---
    QObject::connect(btnTodo, &QPushButton::clicked, [=]() {
        btn7dias->setChecked(false);
        btnMes->setChecked(false);
        btnAnio->setChecked(false);
        aplicarFiltro("todo");
    });

    QObject::connect(btn7dias, &QPushButton::clicked, [=]() {
        btnTodo->setChecked(false);
        btnMes->setChecked(false);
        btnAnio->setChecked(false);
        aplicarFiltro("7dias");
    });

    QObject::connect(btnMes, &QPushButton::clicked, [=]() {
        btnTodo->setChecked(false);
        btn7dias->setChecked(false);
        btnAnio->setChecked(false);
        aplicarFiltro("mes");
    });

    QObject::connect(btnAnio, &QPushButton::clicked, [=]() {
        btnTodo->setChecked(false);
        btn7dias->setChecked(false);
        btnMes->setChecked(false);
        aplicarFiltro("anio");
    });

    // Mostrar “Todo” por defecto al inicio
    btnTodo->setChecked(true);

    return container;
}
// ---------------- KPI GRID ----------------
QWidget* InformesView::createKpiGrid() {
    auto *container = new QWidget;
    auto *grid = new QGridLayout(container);
    grid->setSpacing(16);

    DatabaseManager db;

    // 🟦 Total Donaciones Recibidas
    QJsonArray totalDonacionesArr = db.doGet(R"(
        SELECT COALESCE(SUM(cantidad), 0) AS total
        FROM donaciones_recibidas
    )");
    double totalDonaciones = totalDonacionesArr.isEmpty() ? 0 : totalDonacionesArr[0].toObject().value("total").toDouble();

    // 🟩 Donantes Activos (aquellos que han hecho al menos una donación)
    QJsonArray donantesActivosArr = db.doGet(R"(
        SELECT COUNT(DISTINCT donante_id) AS total
        FROM donaciones_recibidas
        WHERE donante_id IS NOT NULL
    )");
    int donantesActivos = donantesActivosArr.isEmpty() ? 0 : donantesActivosArr[0].toObject().value("total").toInt();

    // 🟨 Donación Promedio
    QJsonArray promedioArr = db.doGet(R"(
        SELECT COALESCE(AVG(cantidad), 0) AS promedio
        FROM donaciones_recibidas
    )");
    double donacionPromedio = promedioArr.isEmpty() ? 0 : promedioArr[0].toObject().value("promedio").toDouble();

    // 🟧 Nuevos Donantes del último mes
    QJsonArray nuevosDonantesArr = db.doGet(R"(
        SELECT COUNT(*) AS nuevos
        FROM donantes
        WHERE created_at >= (CURRENT_DATE - INTERVAL '30 days')
    )");
    int nuevosDonantes = nuevosDonantesArr.isEmpty() ? 0 : nuevosDonantesArr[0].toObject().value("nuevos").toInt();

    // ---------------------- KPIs ----------------------
    grid->addWidget(createKpiCard("Total Donaciones Recibidas",
                                  QString::number(totalDonaciones, 'f', 0),
                                  "+12% vs mes anterior",
                                  "payments", true), 0, 0);

    grid->addWidget(createKpiCard("Donantes Activos",
                                  QString::number(donantesActivos),
                                  "-3% vs mes anterior",
                                  "group", false), 0, 1);

    grid->addWidget(createKpiCard("Donación Promedio",
                                  QString::number(donacionPromedio, 'f', 2),
                                  "+5% vs mes anterior",
                                  "euro", true), 0, 2);

    grid->addWidget(createKpiCard("Nuevos Donantes",
                                  QString::number(nuevosDonantes),
                                  "+8% vs mes anterior",
                                  "person_add", true), 0, 3);

    return container;
}

QWidget* InformesView::createKpiCard(const QString &titulo, const QString &valor, const QString &tendencia, const QString &, bool positiva) {
    auto *card = new QGroupBox;
    card->setStyleSheet("QGroupBox { background: white; border: 1px solid #e2e8f0; border-radius: 12px; }");

    auto *layout = new QVBoxLayout(card);
    layout->setSpacing(4);

    auto *lblTitulo = new QLabel(titulo);
    lblTitulo->setStyleSheet("color: #475569; font-size: 14px; font-weight: 500;");

    auto *lblValor = new QLabel(valor);
    lblValor->setStyleSheet("font-size: 28px; font-weight: 700; color: #0f172a;");

    auto *lblTrend = new QLabel(tendencia);
    lblTrend->setStyleSheet(QString("color: %1; font-size: 13px;").arg(positiva ? "#16a34a" : "#dc2626"));

    layout->addWidget(lblTitulo);
    layout->addWidget(lblValor);
    layout->addWidget(lblTrend);

    return card;
}

// ---------------- GRÁFICOS ----------------
QWidget* InformesView::createGraficos() {
    auto *container = new QWidget;
    auto *grid = new QGridLayout(container);
    grid->setSpacing(5);

    // Crear chart views y almacenarlos en miembros para poder actualizarlos cuando llegue data
    trendChartView_ = createDonationsTrendChart();
    byCategoryChartView_ = createDonationsByCategoryChart();
    bySourceChartView_ = createDonationsBySourceChart();
    topDonorsChartView_ = createTopDonorsChart();
    inventoryChartView_ = createInventoryStatusChart();
    beneficiariesChartView_ = createBeneficiariesGrowthChart();

    // Layout: 2x3
    grid->addWidget(trendChartView_, 0, 0);
    grid->addWidget(byCategoryChartView_, 0, 1);
    grid->addWidget(bySourceChartView_, 0, 2);
    grid->addWidget(topDonorsChartView_, 1, 0);
    grid->addWidget(inventoryChartView_, 1, 1);
    grid->addWidget(beneficiariesChartView_, 1, 2);

    return container;
}

// ---------------- Creadores de gráficos (vistas básicas) ----------------

QChartView* InformesView::createDonationsTrendChart() {
    auto *chart = new QChart;
    chart->setTitle("Tendencia de Donaciones (recibidas vs enviadas)");
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Series vacías (se llenarán en setDonacionesRecibidas / enviadas)
    auto *seriesR = new QLineSeries;
    seriesR->setName("Recibidas");
    auto *seriesE = new QLineSeries;
    seriesE->setName("Enviadas");

    chart->addSeries(seriesR);
    chart->addSeries(seriesE);

    auto *axisX = new QCategoryAxis;
    axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
    chart->addAxis(axisX, Qt::AlignBottom);
    seriesR->attachAxis(axisX);
    seriesE->attachAxis(axisX);

    auto *axisY = new QValueAxis;
    axisY->setLabelFormat("%.2f");
    chart->addAxis(axisY, Qt::AlignLeft);
    seriesR->attachAxis(axisY);
    seriesE->attachAxis(axisY);

    chart->setBackgroundRoundness(10);

    auto *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setStyleSheet("background: transparent;");   // 👈 Hace el fondo transparente

    return view;
}

QChartView* InformesView::createDonationsByCategoryChart() {
    auto *chart = new QChart;
    chart->setTitle("Donaciones por Categoría");
    auto *pie = new QPieSeries;
    chart->addSeries(pie);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->setBackgroundRoundness(10);

    auto *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setStyleSheet("background: transparent;");   // 👈 Hace el fondo transparente
    return view;
}

QChartView* InformesView::createDonationsBySourceChart() {
    auto *chart = new QChart;
    chart->setTitle("Donaciones por Fuente");
    auto *series = new QBarSeries;
    chart->addSeries(series);

    auto *axisX = new QBarCategoryAxis;
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto *axisY = new QValueAxis;
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->setBackgroundRoundness(10);
    series->attachAxis(axisY);

    auto *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setStyleSheet("background: transparent;");   // 👈 Hace el fondo transparente
    return view;
}

QChartView* InformesView::createTopDonorsChart() {
    auto *chart = new QChart;
    chart->setTitle("Top Donantes (monto total)");
    auto *series = new QBarSeries;
    chart->addSeries(series);

    auto *axisX = new QBarCategoryAxis;
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto *axisY = new QValueAxis;
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->setBackgroundRoundness(10);
    series->attachAxis(axisY);

    auto *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setStyleSheet("background: transparent;");   // 👈 Hace el fondo transparente
    return view;
}

QChartView* InformesView::createInventoryStatusChart() {
    auto *chart = new QChart;
    chart->setTitle("Inventario: Stock por Categoría");
    auto *series = new QBarSeries;
    chart->addSeries(series);

    auto *axisX = new QBarCategoryAxis;
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto *axisY = new QValueAxis;
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->setBackgroundRoundness(10);
    series->attachAxis(axisY);

    auto *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setStyleSheet("background: transparent;");   // 👈 Hace el fondo transparente
    return view;
}

QChartView* InformesView::createBeneficiariesGrowthChart() {
    auto *chart = new QChart;
    chart->setTitle("Crecimiento de Beneficiarios");
    auto *series = new QLineSeries;
    series->setName("Beneficiarios");
    chart->addSeries(series);

    auto *axisX = new QCategoryAxis;
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto *axisY = new QValueAxis;
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->setBackgroundRoundness(10);
    series->attachAxis(axisY);

    auto *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setStyleSheet("background: transparent;");   // 👈 Hace el fondo transparente
    return view;
}

// ---------------- Agregadores / helpers ----------------

// Agrega por fecha (se espera que cada objeto tenga un campo "date" ISO y "amount")
void InformesView::aggregateDonationsTrend(const QJsonArray &arr, QMap<QDate, double> &outByDate) {
    outByDate.clear();
    for (const QJsonValue &v : arr) {
        if (!v.isObject()) continue;
        QJsonObject obj = v.toObject();
        QString dateStr = obj.value("date").toString();
        double amount = obj.value("amount").toDouble(0.0);
        if (dateStr.isEmpty()) continue;
        QDate date = QDateTime::fromString(dateStr, Qt::ISODate).date();
        if (!date.isValid()) {
            // intentar yyyy-MM-dd
            date = QDate::fromString(dateStr.left(10), "yyyy-MM-dd");
        }
        if (!date.isValid()) continue;
        outByDate[date] += amount;
    }
}

QMap<QString, double> InformesView::aggregateByStringField(const QJsonArray &arr, const QString &field, const QString &valueField) {
    QMap<QString, double> out;
    for (const QJsonValue &v : arr) {
        if (!v.isObject()) continue;
        QJsonObject obj = v.toObject();
        QString key = obj.value(field).toString();
        double val = obj.value(valueField).toDouble(0.0);
        if (key.isEmpty()) key = QStringLiteral("Sin especificar");
        out[key] += val;
    }
    return out;
}

QMap<QString, double> InformesView::aggregateTopDonors(const QJsonArray &arr, int topN) {
    // Se asume campo "donorId" o "donorName" y "amount"
    QMap<QString, double> totals;
    for (const QJsonValue &v : arr) {
        if (!v.isObject()) continue;
        QJsonObject obj = v.toObject();
        QString donor = obj.value("donorname").toString();
        if (donor.isEmpty()) donor = obj.value("donorId").toString();
        if (donor.isEmpty()) donor = "Anónimo";
        totals[donor] += obj.value("amount").toDouble(0.0);
    }
    // ordenar y tomar topN
    QList<QPair<QString,double>> list;
    for (auto it = totals.cbegin(); it != totals.cend(); ++it) list.append({it.key(), it.value()});
    std::sort(list.begin(), list.end(), [](const QPair<QString,double> &a, const QPair<QString,double> &b){
        return a.second > b.second;
    });
    QMap<QString,double> top;
    int count = 0;
    for (auto &p : list) {
        if (count++ >= topN) break;
        top[p.first] = p.second;
    }
    return top;
}

// ---------------- Setters públicos (reciben JSON y actualizan charts) ----------------

void InformesView::setDonacionesRecibidas(const QJsonArray &arr) {
    donacionesRecibidas_ = arr;
    if (donacionesRecibidasOriginal_.isEmpty())
        donacionesRecibidasOriginal_ = arr;

    updateTrendChart(); // ✅ ahora todo el dibujo se hace aquí
    updateCategoryChart();
    updateTopDonorsChart();
}

void InformesView::setDonacionesEnviadas(const QJsonArray &arr) {
    donacionesEnviadas_ = arr;
    if (donacionesEnviadasOriginal_.isEmpty())
        donacionesEnviadasOriginal_ = arr;

    updateTrendChart(); // ✅ mismo mecanismo
    updateCategoryChart();
    updateTopDonorsChart();
}

void InformesView::setInventario(const QJsonArray &arr) {
    inventario_ = arr;
    if (inventarioOriginal_.isEmpty())
        inventarioOriginal_ = arr; // solo guardar la primera vez

    if (!inventoryChartView_) return;
    auto byCat = aggregateByStringField(inventario_, "category", "stock"); // se espera campo 'stock' numérico
    QChart *c = inventoryChartView_->chart();
    c->removeAllSeries();
    QBarSeries *series = new QBarSeries;
    QBarSet *set = new QBarSet("Stock");
    QStringList cats;
    double maxv = 0;
    for (auto it = byCat.cbegin(); it != byCat.cend(); ++it) {
        *set << it.value();
        cats << it.key();
        if (it.value() > maxv) maxv = it.value();
    }
    series->append(set);
    c->addSeries(series);
    QBarCategoryAxis *axisX = new QBarCategoryAxis;
    axisX->append(cats);
    c->removeAxis(c->axisX());
    c->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, qMax(1.0, maxv * 1.2));
    c->removeAxis(c->axisY());
    c->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
}

void InformesView::setDonantes(const QJsonArray &arr) {
    donantes_ = arr;
    if (donantesOriginal_.isEmpty())
        donantesOriginal_ = arr;

    if (!bySourceChartView_) return;

    // --- Agrupar por fuente ---
    QMap<QString, double> byFuente;
    for (const QJsonValue &v : arr) {
        if (!v.isObject()) continue;
        QJsonObject obj = v.toObject();
        QString nombre = obj.value("donorname").toString();
        double monto = obj.value("amount").toDouble(0.0);

        QString tipo;
        if (nombre.contains("Empresa", Qt::CaseInsensitive))
            tipo = "Empresa";
        else if (nombre.contains("ONG", Qt::CaseInsensitive))
            tipo = "ONG";
        else
            tipo = "Individual";
        byFuente[tipo] += monto;
    }

    // --- Construir el gráfico limpio ---
    QChart *chart = bySourceChartView_->chart();
    chart->removeAllSeries();
    for (auto *axis : chart->axes()) {
        chart->removeAxis(axis);
        delete axis;
    }

    QBarSeries *series = new QBarSeries;
    QBarSet *set = new QBarSet("Montos por Fuente");
    QStringList categorias;
    double maxv = 0;

    for (auto it = byFuente.cbegin(); it != byFuente.cend(); ++it) {
        categorias << it.key();
        *set << it.value();
        maxv = qMax(maxv, it.value());
    }

    series->append(set);
    chart->addSeries(series);

    auto *axisX = new QBarCategoryAxis;
    axisX->append(categorias);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto *axisY = new QValueAxis;
    axisY->setRange(0, qMax(1.0, maxv * 1.2));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
}

void InformesView::setBeneficiarios(const QJsonArray &arr) {
    beneficiarios_ = arr;
    if (beneficiariosOriginal_.isEmpty())
        beneficiariosOriginal_ = arr;

    if (!beneficiariesChartView_) return;

    // --- Contar por fecha ---
    QMap<QDate,double> byDate;
    for (const QJsonValue &v : beneficiarios_) {
        if (!v.isObject()) continue;
        QJsonObject obj = v.toObject();
        QDate date = QDateTime::fromString(obj.value("date").toString(), Qt::ISODate).date();
        if (date.isValid()) byDate[date] += 1.0;
    }

    // --- Limpiar completamente el gráfico ---
    QChart *c = beneficiariesChartView_->chart();
    c->removeAllSeries();
    for (auto *axis : c->axes()) {
        c->removeAxis(axis);
        delete axis;
    }

    // --- Nueva serie ---
    QLineSeries *series = new QLineSeries;
    series->setName("Beneficiarios");

    QList<QDate> dates = byDate.keys();
    std::sort(dates.begin(), dates.end());
    QCategoryAxis *axisX = new QCategoryAxis;
    double maxv = 0;
    int idx = 0;
    for (const QDate &d : dates) {
        double val = byDate[d];
        series->append(idx, val);
        axisX->append(d.toString("dd MMM"), idx);
        maxv = qMax(maxv, val);
        idx++;
    }

    c->addSeries(series);
    c->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, qMax(1.0, maxv * 1.2));
    c->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
}

void InformesView::updateTrendChart() {
    if (!trendChartView_) return;
    QChart *chart = trendChartView_->chart();
    if (!chart) return;

    // Buscar o crear series
    QLineSeries *seriesR = nullptr;
    QLineSeries *seriesE = nullptr;
    for (auto *s : chart->series()) {
        if (auto *ls = qobject_cast<QLineSeries*>(s)) {
            if (ls->name() == "Recibidas") seriesR = ls;
            else if (ls->name() == "Enviadas") seriesE = ls;
        }
    }
    if (!seriesR) { seriesR = new QLineSeries; seriesR->setName("Recibidas"); chart->addSeries(seriesR); }
    if (!seriesE) { seriesE = new QLineSeries; seriesE->setName("Enviadas"); chart->addSeries(seriesE); }

    seriesR->clear();
    seriesE->clear();

    // --- Combinar fechas ---
    QMap<QDate, double> byRec, byEnv;
    aggregateDonationsTrend(donacionesRecibidas_, byRec);
    aggregateDonationsTrend(donacionesEnviadas_, byEnv);

    QList<QDate> allDates = byRec.keys();
    for (const QDate &d : byEnv.keys())
        if (!allDates.contains(d))
            allDates.append(d);
    std::sort(allDates.begin(), allDates.end());

    // --- Poblar puntos ---
    int idx = 0;
    for (const QDate &d : allDates) {
        seriesR->append(idx, byRec.value(d, 0.0));
        seriesE->append(idx, byEnv.value(d, 0.0));
        idx++;
    }

    // --- Ejes ---
    chart->removeAxis(chart->axisX());
    chart->removeAxis(chart->axisY());

    auto *axisX = new QCategoryAxis;
    axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
    int x = 0;
    for (const QDate &d : allDates)
        axisX->append(d.toString("dd MMM"), x++);

    chart->addAxis(axisX, Qt::AlignBottom);
    seriesR->attachAxis(axisX);
    seriesE->attachAxis(axisX);

    auto *axisY = new QValueAxis;
    double maxY = 0;
    for (auto *s : {seriesR, seriesE}) {
        for (const QPointF &p : s->points())
            maxY = qMax(maxY, p.y());
    }
    axisY->setRange(0, qMax(1.0, maxY * 1.2));
    chart->addAxis(axisY, Qt::AlignLeft);
    seriesR->attachAxis(axisY);
    seriesE->attachAxis(axisY);
}

void InformesView::updateCategoryChart() {
    if (!byCategoryChartView_) return;
    QChart *c = byCategoryChartView_->chart();
    c->removeAllSeries();

    auto byCat = aggregateByStringField(donacionesRecibidas_, "category");
    if (byCat.isEmpty()) {
        c->setTitle("Donaciones por categoría (sin datos)");
        return;
    }

    QPieSeries *pie = new QPieSeries;
    for (auto it = byCat.cbegin(); it != byCat.cend(); ++it)
        pie->append(it.key(), it.value());
    c->addSeries(pie);
    c->setTitle("Donaciones por categoría");
}

void InformesView::updateTopDonorsChart() {
    if (!topDonorsChartView_) return;
    QChart *c = topDonorsChartView_->chart();
    c->removeAllSeries();

    auto top = aggregateTopDonors(donacionesRecibidas_, 8);
    if (top.isEmpty()) {
        c->setTitle("Top Donantes (sin datos)");
        return;
    }

    QBarSeries *series = new QBarSeries;
    QBarSet *set = new QBarSet("Monto");
    QStringList categories;
    for (auto it = top.cbegin(); it != top.cend(); ++it) {
        *set << it.value();
        categories << it.key();
    }
    series->append(set);
    c->addSeries(series);

    auto *axisX = new QBarCategoryAxis;
    axisX->append(categories);
    for (auto *a : c->axes(Qt::Horizontal)) c->removeAxis(a);
    c->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto *axisY = new QValueAxis;
    for (auto *a : c->axes(Qt::Vertical)) c->removeAxis(a);
    c->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    c->setTitle("Top Donantes");
}

