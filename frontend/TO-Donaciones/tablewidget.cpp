#include "tablewidget.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QJsonValue>
#include <QDebug>

TableWidget::TableWidget(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    m_table = new QTableWidget;
    m_table->verticalHeader()->hide();
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setShowGrid(false);

    m_table->setStyleSheet(R"(
        QHeaderView::section {
            background-color: #f9fafb;
            color: #374151;
            text-transform: uppercase;
            font-weight: bold;
            font-size: 12px;
            padding: 10px 12px;
            border: none;
            border-bottom: 1px solid #e5e7eb;
        }
        QTableWidget {
            background-color: #ffffff;
            gridline-color: #e5e7eb;
        }
        QTableWidget::item {
            color: #111318;
            font-size: 13px;
            padding: 6px;
        }
        QTableWidget::item:selected {
            background-color: #dbeafe;
        }
    )");

    layout->addWidget(m_table);
}

QPushButton* TableWidget::createIconButton(const QString &iconPath, const QString &tooltip, const QString &color)
{
    QPushButton *btn = new QPushButton;
    btn->setToolTip(tooltip);
    btn->setCursor(Qt::PointingHandCursor);
    btn->setFixedSize(28, 28);
    btn->setIcon(QIcon(iconPath));
    btn->setIconSize(QSize(16, 16));

    QString iconColor = color.isEmpty() ? "#374151" : color;
    btn->setStyleSheet(QString(R"(
        QPushButton {
            background-color: transparent;
            border: none;
            border-radius: 6px;
            color: %1;
        }
        QPushButton:hover {
            background-color: #f3f4f6;
        }
    )").arg(iconColor));

    return btn;
}

QWidget* TableWidget::createActionsWidget(int id)
{
    QWidget *widget = new QWidget;
    auto *layout = new QHBoxLayout(widget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(4);

    QPushButton *viewBtn = createIconButton(":/icons/tabla/visibility.svg", "Ver", "#6b7280");
    QPushButton *editBtn = createIconButton(":/icons/tabla/edit.svg", "Editar", "#2563eb");
    QPushButton *deleteBtn = createIconButton(":/icons/tabla/delete.svg", "Eliminar", "#dc2626");

    layout->addWidget(viewBtn);
    layout->addWidget(editBtn);
    layout->addWidget(deleteBtn);
    layout->addStretch();

    connect(viewBtn, &QPushButton::clicked, this, [=]() { emit actionTriggered(id, "ver"); });
    connect(editBtn, &QPushButton::clicked, this, [=]() { emit actionTriggered(id, "editar"); });
    connect(deleteBtn, &QPushButton::clicked, this, [=]() { emit actionTriggered(id, "eliminar"); });

    return widget;
}

void TableWidget::loadFromJson(const QJsonArray &data, bool withActions)
{
    if (data.isEmpty()) {
        m_table->clear();
        m_table->setRowCount(0);
        m_table->setColumnCount(0);
        return;
    }

    QJsonObject first = data.first().toObject();
    QStringList keys = first.keys();

    int columnCount = keys.size() + (withActions ? 1 : 0);
    m_table->setColumnCount(columnCount);

    // Headers dinámicos
    QStringList headers = keys;
    if (withActions) headers << "Acciones";
    m_table->setHorizontalHeaderLabels(headers);

    m_table->setRowCount(data.size());

    for (int row = 0; row < data.size(); ++row) {
        QJsonObject obj = data[row].toObject();

        for (int col = 0; col < keys.size(); ++col) {
            QString key = keys[col];
            QString value;

            if (obj[key].isDouble())
                value = QString::number(obj[key].toDouble());
            else
                value = obj[key].toString();

            auto *item = new QTableWidgetItem(value);
            item->setForeground(QBrush(QColor("#111318")));
            m_table->setItem(row, col, item);
        }

        if (withActions) {
            int id = obj.contains("id") ? obj["id"].toInt() : row;
            m_table->setCellWidget(row, keys.size(), createActionsWidget(id));
        }
    }

    // Ajuste automático
    for (int i = 0; i < columnCount; ++i)
        m_table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);

    if (!withActions)
        m_table->horizontalHeader()->setStretchLastSection(true);
}

