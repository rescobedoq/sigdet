#include "conexiondbhelperController.h"
#include "databasemanagerController.h"

ConexionDBHelper::ConexionDBHelper(QObject *parent)
    : QObject(parent)
{
}

// -------------------------------------------------------
// 🔴 Conectar señal de eliminar
// -------------------------------------------------------
void ConexionDBHelper::conexionDBEliminar(QWidget *context,
                                          TableWidgetCard *tablaWidget,
                                          const QStringList &headers,
                                          const QString &tabla,
                                          std::function<QJsonArray()> getDataFn)
{
    QObject::connect(tablaWidget, &TableWidgetCard::actionTriggered,
                     context, [context, tablaWidget, headers, tabla, getDataFn](const QString &id, const QString &action) {
                         if (action == "eliminar") {
                             auto reply = QMessageBox::question(context,
                                                                "Eliminar registro",
                                                                "⚠️ ¿Estás seguro de que deseas eliminar este registro?",
                                                                QMessageBox::Yes | QMessageBox::No);

                             if (reply == QMessageBox::Yes) {
                                 DatabaseManager db;
                                 if (db.doRemove(tabla, id)) {
                                     QMessageBox::information(context, "Eliminación exitosa", "✅ El registro ha sido eliminado.");
                                     tablaWidget->reloadData(getDataFn(), headers);
                                 } else {
                                     QMessageBox::critical(context, "Error", "❌ No se pudo eliminar el registro.");
                                 }
                             }
                         }
                     });
}

// -------------------------------------------------------
// 🟢 Conectar señal de actualizar
// -------------------------------------------------------
void ConexionDBHelper::conexionDBActualizar(QWidget *context,
                                            TableWidgetCard *tablaWidget,
                                            const QStringList &headers,
                                            const QString &tabla,
                                            std::function<QJsonArray()> getDataFn)
{
    QObject::connect(tablaWidget, &TableWidgetCard::actionTriggeredWithData,
                     context, [context, tablaWidget, headers, tabla, getDataFn](const QString &id,
                                                                       const QString &action,
                                                                       const QJsonObject &updatedData) {
                         if (action == "confirmar") {
                             DatabaseManager db;
                             if (db.doUpdate(tabla, id, updatedData)) {
                                 QMessageBox::information(context, "Actualización exitosa", "✅ El registro ha sido actualizado.");
                                 tablaWidget->reloadData(getDataFn(), headers);
                             } else {
                                 QMessageBox::critical(context, "Error", "❌ No se pudo actualizar el registro.");
                             }
                         }
                     });
}
