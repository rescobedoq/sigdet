#ifndef CONEXIONDBHELPERCONTROLLER_H
#define CONEXIONDBHELPERCONTROLLER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QStringList>
#include <QMessageBox>
#include "tablewidgetcardView.h"

class ConexionDBHelper : public QObject
{
    Q_OBJECT
public:
    explicit ConexionDBHelper(QObject *parent = nullptr);

    // Conecta señal para eliminar registros
    static void conexionDBEliminar(QWidget *context,
                                   TableWidgetCard *tablaWidget,
                                   const QStringList &headers,
                                   const QString &tabla,
                                   std::function<QJsonArray()> getDataFn);

    // Conecta señal para actualizar registros
    static void conexionDBActualizar(QWidget *context,
                                     TableWidgetCard *tablaWidget,
                                     const QStringList &headers,
                                     const QString &tabla,
                                     std::function<QJsonArray()> getDataFn);
};
#endif // CONEXIONDBHELPERCONTROLLER_H
