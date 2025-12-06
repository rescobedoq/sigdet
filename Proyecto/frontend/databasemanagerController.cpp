#include "databasemanagerController.h"

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject(parent)
{
    // Crear la conexión con nombre único (si no existe)
    if (!QSqlDatabase::contains("donaciones_conn")) {
        db = QSqlDatabase::addDatabase("QPSQL", "donaciones_conn");
        db.setHostName("127.0.0.1");
        db.setPort(5432);
        db.setDatabaseName("donaciones_db");
        db.setUserName("donaciones_user");
        db.setPassword("donaciones_pass");
    } else {
        db = QSqlDatabase::database("donaciones_conn");
    }
}

bool DatabaseManager::open() {

    if (!db.isOpen()) {
        if (!db.open()) {
            qWarning() << "❌ Error al conectar a la BD:" << db.lastError().text();
            return false;
        }
        qDebug() << "✅ Conexión establecida con la base de datos";
    }
    return true;
}

void DatabaseManager::close() {
    if (db.isOpen()) {
        db.close();
        qDebug() << "🔒 Conexión cerrada";
    }
}

QJsonArray DatabaseManager::doGet(const QString &queryStr, const QVariantList &params) {
    QJsonArray result;

    if (!open())
        return result;

    QSqlQuery query(db);

    bool success = false;
    if (params.isEmpty()) {
        // No hay parámetros → ejecutar directamente
        success = query.exec(queryStr);
    } else {
        // Hay parámetros → preparar y vincular
        query.prepare(queryStr);
        for (int i = 0; i < params.size(); ++i)
            query.bindValue(i, params[i]);
        success = query.exec();
    }

    if (!success) {
        qWarning() << "❌ Error en SELECT:" << query.lastError().text();
        qWarning() << "Consulta fallida:" << queryStr;
        return result;
    }

    while (query.next()) {
        QJsonObject row;
        for (int i = 0; i < query.record().count(); ++i) {
            QString key = query.record().fieldName(i);
            row.insert(key, QJsonValue::fromVariant(query.value(i)));
        }
        result.append(row);
    }

    return result;
}
bool DatabaseManager::doRemove(const QString &tableName, const QString &id)
{
    if (!open())
        return false;

    // Verificar que el nombre de tabla no esté vacío ni contenga caracteres peligrosos
    QRegularExpression validName("^[A-Za-z_][A-Za-z0-9_]*$");
    if (!validName.match(tableName).hasMatch()) {
        qWarning() << "❌ Nombre de tabla no válido:" << tableName;
        return false;
    }

    // Crear consulta segura con parámetro enlazado
    QString queryStr = QString("DELETE FROM %1 WHERE id = ?;").arg(tableName);

    QSqlQuery query(db);
    query.prepare(queryStr);
    query.bindValue(0, id);

    if (!query.exec()) {
        qWarning() << "❌ Error al eliminar registro de" << tableName << ":" << query.lastError().text();
        return false;
    }

    qDebug() << "✅ Registro eliminado correctamente de" << tableName << "con ID:" << id;
    return true;
}
bool DatabaseManager::doUpdate(const QString &tableName, const QString &id, const QJsonObject &updatedData)
{
    if (!open()) {
        qWarning() << "❌ Error de conexión: no se pudo abrir la base de datos.";
        return false;
    }

    if (updatedData.isEmpty()) {
        qWarning() << "⚠️ Sin datos: no hay datos para actualizar.";
        return false;
    }

    QStringList setClauses;

    // Construir SET dinámico con valores seguros
    for (auto it = updatedData.begin(); it != updatedData.end(); ++it) {
        QString key = it.key();

        // 🔁 Reemplazar automáticamente "fecha_creacion" → "created_at"
        if (key == "fecha_creacion")
            key = "created_at";

        if (key == "id")
            continue;

        QString valueStr = it.value().toVariant().toString();
        valueStr.replace("'", "''"); // escapar comillas simples

        setClauses << QString("%1 = '%2'").arg(key, valueStr);
    }

    QString queryStr = QString("UPDATE %1 SET %2 WHERE id = '%3';")
                           .arg(tableName)
                           .arg(setClauses.join(", "))
                           .arg(id);

    QSqlQuery query(QSqlDatabase::database(db.connectionName(), false));

    if (!query.exec(queryStr)) {
        qWarning() << "❌ Error al actualizar registro en" << tableName << ":"
                   << query.lastError().text()
                   << "\nSQL:" << queryStr;
        return false;
    }

    qDebug() << "✅ Registro actualizado correctamente en" << tableName << "| ID:" << id;
    return true;
}
QJsonArray DatabaseManager::getColumns(const QString &tableName)
{
    QJsonArray result;

    if (!open())
        return result;

    // Validar el nombre de la tabla
    QRegularExpression validName("^[A-Za-z_][A-Za-z0-9_]*$");
    if (!validName.match(tableName).hasMatch()) {
        qWarning() << "❌ Nombre de tabla no válido:" << tableName;
        return result;
    }

    QString queryStr = R"(
        SELECT column_name
        FROM information_schema.columns
        WHERE table_name = :tableName
        AND column_name NOT IN ('id', 'created_at', 'updated_at')
        ORDER BY ordinal_position;
    )";

    QSqlQuery query(db);
    query.prepare(queryStr);
    query.bindValue(":tableName", tableName);

    if (!query.exec()) {
        qWarning() << "❌ Error al obtener columnas de" << tableName << ":" << query.lastError().text();
        return result;
    }

    while (query.next()) {
        QJsonObject col;
        col["column_name"] = query.value("column_name").toString();
        result.append(col);
    }

    return result;
}

bool DatabaseManager::doInsert(const QString &tableName, const QJsonObject &data)
{
    if (!open())
        return false;

    if (data.isEmpty()) {
        qWarning() << "⚠️ No hay datos para insertar en" << tableName;
        return false;
    }

    // Validar nombre de tabla
    QRegularExpression validName("^[A-Za-z_][A-Za-z0-9_]*$");
    if (!validName.match(tableName).hasMatch()) {
        qWarning() << "❌ Nombre de tabla no válido:" << tableName;
        return false;
    }

    QStringList columns;
    QStringList placeholders;
    QVariantList values;

    for (auto it = data.begin(); it != data.end(); ++it) {
        columns << it.key();
        placeholders << "?";
        values << it.value().toVariant();
    }

    QString queryStr = QString("INSERT INTO %1 (%2) VALUES (%3);")
                           .arg(tableName)
                           .arg(columns.join(", "))
                           .arg(placeholders.join(", "));

    QSqlQuery query(db);
    query.prepare(queryStr);

    for (int i = 0; i < values.size(); ++i)
        query.bindValue(i, values[i]);

    if (!query.exec()) {
        qWarning() << "❌ Error al insertar en" << tableName << ":" << query.lastError().text();
        qWarning() << "SQL:" << queryStr;
        return false;
    }

    qDebug() << "✅ Registro insertado correctamente en" << tableName;
    return true;
}
QMap<QString, QString> DatabaseManager::getForeignKeys(const QString &tableName)
{
    QMap<QString, QString> fks;

    if (!open())
        return fks;

    // Validar nombre de tabla
    QRegularExpression validName("^[A-Za-z_][A-Za-z0-9_]*$");
    if (!validName.match(tableName).hasMatch()) {
        qWarning() << "❌ Nombre de tabla no válido:" << tableName;
        return fks;
    }

    QString queryStr = R"(
        SELECT
            kcu.column_name,
            ccu.table_name AS foreign_table_name
        FROM
            information_schema.table_constraints AS tc
            JOIN information_schema.key_column_usage AS kcu
              ON tc.constraint_name = kcu.constraint_name
              AND tc.table_schema = kcu.table_schema
            JOIN information_schema.constraint_column_usage AS ccu
              ON ccu.constraint_name = tc.constraint_name
              AND ccu.table_schema = tc.table_schema
        WHERE tc.constraint_type = 'FOREIGN KEY' AND tc.table_name = :tableName;
    )";

    QSqlQuery query(db);
    query.prepare(queryStr);
    query.bindValue(":tableName", tableName);

    if (!query.exec()) {
        qWarning() << "❌ Error al obtener foreign keys de" << tableName << ":" << query.lastError().text();
        return fks;
    }

    while (query.next()) {
        QString colName = query.value("column_name").toString();
        QString fkTable = query.value("foreign_table_name").toString();
        fks[colName] = fkTable;
    }

    return fks;
}
bool DatabaseManager::doLogin(const QString &username, const QString &password)
{
    if (!open())
        return false;

    QString queryStr = R"(
        SELECT 1
        FROM users
        WHERE username = ? AND password_u = ?
        LIMIT 1;
    )";

    QSqlQuery query(db);
    query.prepare(queryStr);
    query.bindValue(0, username);
    query.bindValue(1, password);

    if (!query.exec()) {
        qWarning() << "❌ Error al validar login:" << query.lastError().text();
        return false;
    }

    // Si hay resultado → credenciales válidas
    if (query.next()) {
        qDebug() << "✅ Usuario autenticado:" << username;
        return true;
    }

    qWarning() << "⚠️ Usuario o contraseña incorrectos";
    return false;
}
