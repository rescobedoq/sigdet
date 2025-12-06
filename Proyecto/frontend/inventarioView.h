#ifndef INVENTARIOVIEW_H
#define INVENTARIOVIEW_H

#include <QWidget>
#include <qboxlayout.h>
#include <QScrollArea>
#include "tablewidgetcardView.h"
class QTableWidget;
class QLineEdit;
class QPushButton;

class InventarioView : public QWidget
{
    Q_OBJECT
public:
    explicit InventarioView(QWidget *parent = nullptr);

private:
    void setupHeader(QVBoxLayout *mainLayout);
    void setupControls(QVBoxLayout *mainLayout);
    void setupChartCard(QVBoxLayout *mainLayout, const QJsonArray &data);
    void setupChartCardAt(int insertIndex, const QJsonArray &data);
    void setupTableCard(QVBoxLayout *mainLayout, const QJsonArray &data);
    void filterTableByName(const QString &text);
    void exportTableToCsv(const QString &filePath);
    TableWidgetCard *tablaWidget = nullptr;
private:
    QLineEdit *m_searchEdit = nullptr;
    QTableWidget *m_table = nullptr;
    QPushButton *m_btnViewList = nullptr;
    QPushButton *m_btnViewGrid = nullptr;

    QWidget *m_gridContainer = nullptr;
    QScrollArea *m_gridScroll = nullptr;
    QVBoxLayout *m_mainLayout = nullptr;
    QJsonArray getInventario();
    QFrame *chartCard = nullptr;
    QVBoxLayout *mainLayout = nullptr;
    void reloadChart();
};
#endif // INVENTARIOVIEW_H
