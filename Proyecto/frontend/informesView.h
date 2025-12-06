#ifndef INFORMESVIEW_H
#define INFORMESVIEW_H

#pragma once

#include <QWidget>
#include <QJsonArray>
#include <QJsonObject>
#include <QtCharts/QChartView>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QPushButton;
class QGridLayout;
class QGroupBox;
QT_END_NAMESPACE

class InformesView : public QWidget
{
    Q_OBJECT
public:
    explicit InformesView(QWidget *parent = nullptr);

    // Métodos públicos para recibir datos JSON (ya parseados a QJsonArray)
    void setDonacionesRecibidas(const QJsonArray &arr);
    void updateTopDonorsChart();
    void updateCategoryChart();
    void setDonacionesEnviadas(const QJsonArray &arr);
    void setInventario(const QJsonArray &arr);
    void setDonantes(const QJsonArray &arr);
    void setBeneficiarios(const QJsonArray &arr);
    void updateTrendChart();
private:
    // UI builders
    QWidget* createHeader();
    QWidget* createFiltros();
    QWidget* createKpiGrid();
    QWidget* createKpiCard(const QString &titulo, const QString &valor, const QString &tendencia, const QString &icon, bool positiva);
    QWidget* createGraficos();

    // Creadores de gráficos (devuelven QChartView*)
    QChartView* createDonationsTrendChart();           // serie temporal (recebidas - enviadas)
    QChartView* createDonationsByCategoryChart();      // pastel o barras por categoría
    QChartView* createDonationsBySourceChart();        // barras por fuente (web, offline, transferencia, etc.)
    QChartView* createTopDonorsChart();                // barras horizontales top donantes
    QChartView* createInventoryStatusChart();          // barras de stock por categoría
    QChartView* createBeneficiariesGrowthChart();      // linea de crecimiento beneficiarios

    // Helpers para parseo / agregación
    void aggregateDonationsTrend(const QJsonArray &arr, QMap<QDate, double> &outByDate);
    QMap<QString, double> aggregateByStringField(const QJsonArray &arr, const QString &field, const QString &valueField = "amount");
    QMap<QString, double> aggregateTopDonors(const QJsonArray &arr, int topN = 10);

    // Datos en memoria (raws JSON)
    QJsonArray donacionesRecibidas_;
    QJsonArray donacionesEnviadas_;
    QJsonArray inventario_;
    QJsonArray donantes_;
    QJsonArray beneficiarios_;

    // Datos originales (sin filtrar)
    QJsonArray donacionesRecibidasOriginal_;
    QJsonArray donacionesEnviadasOriginal_;
    QJsonArray inventarioOriginal_;
    QJsonArray donantesOriginal_;
    QJsonArray beneficiariosOriginal_;

    // Punteros a vistas de chart para actualizarlas
    QChartView *trendChartView_ = nullptr;
    QChartView *byCategoryChartView_ = nullptr;
    QChartView *bySourceChartView_ = nullptr;
    QChartView *topDonorsChartView_ = nullptr;
    QChartView *inventoryChartView_ = nullptr;
    QChartView *beneficiariesChartView_ = nullptr;
};

#endif // INFORMESVIEW_H
