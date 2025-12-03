#ifndef DATABASEMANAGERCONTROLLER_H
#define DATABASEMANAGERCONTROLLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QLibraryInfo>

class DatabaseManager : public QObject {
    Q_OBJECT

public:
    explicit DatabaseManager(QObject *parent = nullptr);

    // Abre conexión
    bool open();

    // Cierra conexión
    void close();

    // Ejecuta SELECT y devuelve resultados en QJsonArray
    QJsonArray doGet(const QString &queryStr, const QVariantList &params = {});
    bool doRemove(const QString &tableName, const QString &id);
    bool doUpdate(const QString &tableName, const QString &id, const QJsonObject &updatedData);
    QJsonArray getColumns(const QString &tableName);
    bool doInsert(const QString &tableName, const QJsonObject &data);
    QMap<QString, QString> getForeignKeys(const QString &tableName);
    bool doLogin(const QString &username, const QString &password);
private:
    QSqlDatabase db;
};

#endif // DATABASEMANAGERCONTROLLER_H
