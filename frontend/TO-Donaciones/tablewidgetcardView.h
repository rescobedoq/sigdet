#pragma once
#include <QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QJsonArray>
#include <QJsonObject>
#include <QMenu>
#include <QCalendarWidget>
#include <QDate>
#include <QDialog>
#include <QAction>

class TableWidgetCard : public QWidget
{
    Q_OBJECT

public:
    explicit TableWidgetCard(const QString &title,
                             const QJsonArray &data,
                             const QString &categoryColumn,
                             QWidget *parent = nullptr,
                             const QStringList &headers = {});
    void reloadData(const QJsonArray &newData, const QStringList &headers);

signals:
    void actionTriggered(const QString &id, const QString &action);
    void actionTriggeredWithData(const QString &id, const QString &action, const QJsonObject &updatedData);
private slots:
    void onSearchTextChanged(const QString &text);
    void onFilterCategoryChanged(const QString &category);
    void onExportCsv();
    void onFilterDateChanged(const QDate &date);
    void applyFilters();   // 👈 declara esta función aquí
private:
    QTableWidget *m_table;
    QTableWidget *m_actionTable;
    QLineEdit *m_searchEdit;
    QLabel *m_catText;
    QLabel *m_fechaText = nullptr;
    QString m_currentCategory = "Todos";
    QString m_currentDate = "";  // formato yyyy-MM-dd
    QString m_categoryColumn;
    QJsonArray m_originalData;
    void exportTableToCsv(const QString &filePath);
    void loadTable(const QJsonArray &data, const QStringList &headers);
    QWidget *createActionsWidget(int id);
    QPushButton *createIconButton(const QString &iconPath, const QString &tooltip, const QString &color = "");
    void setupTableHeaders(const QStringList &receivedHeaders, int rowCount);
    void populateRow(int row, const QJsonObject &obj, const QStringList &headers);
    QWidget *createActionButtons(int row, const QJsonObject &obj, const QStringList &headers, bool editing);
    QPushButton *createIconButton(const QString &iconPath, const QString &tooltip, const QColor &hoverColor);
    void enableRowEditing(int row, const QStringList &headers);
    void confirmRowEdit(int row, const QJsonObject &obj, const QStringList &headers);
    void cancelRowEdit(int row, const QJsonObject &obj, const QStringList &headers);
    QJsonArray m_currentData;
};
