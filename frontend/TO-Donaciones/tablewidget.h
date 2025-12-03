#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QJsonArray>
#include <QJsonObject>
#include <QPushButton>

class TableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TableWidget(QWidget *parent = nullptr);
    void loadFromJson(const QJsonArray &data, bool withActions = true);

signals:
    void actionTriggered(int id, const QString &action);

private:
    QTableWidget *m_table;

    QWidget* createActionsWidget(int id);
    QPushButton* createIconButton(const QString &iconPath, const QString &tooltip, const QString &color = "");
};
