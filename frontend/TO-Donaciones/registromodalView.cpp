#include "registromodalView.h"
#include "databasemanagerController.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include <QLineEdit>
#include <QComboBox>

RegistroModal::RegistroModal(const QString &nombreTabla, QWidget *parent)
    : QDialog(parent), nombreTabla(nombreTabla)
{
    setWindowTitle("Registrar en " + nombreTabla);
    setModal(true);


    // Fondo blanco con borde redondeado y sombra
    this->setStyleSheet("background-color:white; border-radius:12px;");
    auto *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(20);
    shadow->setOffset(0,0);
    shadow->setColor(QColor(0,0,0,50));
    this->setGraphicsEffect(shadow);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(24,24,24,24);
    mainLayout->setSpacing(20);

    auto *titulo = new QLabel("Registrar nuevo registro en '" + nombreTabla + "'");
    titulo->setStyleSheet("font-size:20px; font-weight:700; color:#1e293b;");
    mainLayout->addWidget(titulo);

    gridLayout = new QGridLayout;
    gridLayout->setHorizontalSpacing(20);
    gridLayout->setVerticalSpacing(12);
    construirFormulario();
    mainLayout->addLayout(gridLayout);

    auto *btnGuardar = new QPushButton("Guardar");
    btnGuardar->setStyleSheet(R"(
        QPushButton {
            background-color:#2563eb;
            color:white;
            font-weight:600;
            border:none;
            border-radius:8px;
            padding:10px 20px;
            font-size:16px;
        }
        QPushButton:hover {
            background-color:#1d4ed8;
        }
    )");
    connect(btnGuardar,&QPushButton::clicked,this,&RegistroModal::guardarRegistro);
    mainLayout->addWidget(btnGuardar,0,Qt::AlignRight);
    adjustSize();
}

bool RegistroModal::esForeignKey(const QString &columna, QString &fkTable)
{
    DatabaseManager db;
    QMap<QString, QString> fks = db.getForeignKeys(nombreTabla); // columna->tabla FK
    if(fks.contains(columna)){
        fkTable = fks[columna];
        return true;
    }
    return false;
}

void RegistroModal::construirFormulario()
{
    DatabaseManager db;
    QJsonArray columnas = db.getColumns(nombreTabla); // Devuelve column_name

    if(columnas.isEmpty()){
        auto *lbl = new QLabel("⚠️ No se encontraron columnas para esta tabla.");
        lbl->setStyleSheet("color:#ef4444; font-weight:500;");
        gridLayout->addWidget(lbl,0,0);
        return;
    }

    int row=0, col=0;
    for(const QJsonValue &c: columnas){
        QString nombreCol = c.toObject().value("column_name").toString();

        auto *label = new QLabel(nombreCol + ":");
        label->setStyleSheet("font-weight:600; color:#1e293b;");

        QString fkTable;
        QWidget *campoWidget = nullptr;

        if (esForeignKey(nombreCol, fkTable)) {
            // Es FK → crear QComboBox
            auto *combo = new QComboBox;
            combo->setStyleSheet(R"(
        QComboBox {
            border:1px solid #cbd5e1;
            border-radius:6px;
            padding:4px 6px;
            background-color:#f8fafc;
            color:#1e293b;
            }
            QComboBox:focus {
                border:1.5px solid #2563eb;
            }
            /* 🔹 Menú desplegable (lista) */
            QComboBox QAbstractItemView {
                background-color: #111;      /* Fondo negro */
                color: #fff;                 /* Texto blanco */
                border: 1px solid #333;
                selection-background-color: #2563eb; /* Azul selección */
                selection-color: white;
            }
            /* 🔹 Flecha del combo */
            QComboBox::drop-down {
                border: none;
                width: 25px;
            }
            QComboBox::down-arrow {
                image: url(:/icons/tabla/expand_more.svg);
                width: 16px;
                height: 16px;
            }
        )");

            // 🔹 Buscar qué columna descriptiva usar (nombre o descripcion)
            QJsonArray fkColumns = db.getColumns(fkTable);
            QString displayColumn;

            for (const QJsonValue &colVal : fkColumns) {
                QString colName = colVal.toObject().value("column_name").toString().toLower();
                if (colName == "nombre") {
                    displayColumn = "nombre";
                    break;
                } else if (colName == "descripcion") {
                    displayColumn = "descripcion";
                    // no break, por si luego aparece "nombre"
                }
            }

            // 🔹 Construir consulta para obtener ID + columna descriptiva
            QString query;
            if (!displayColumn.isEmpty())
                query = QString("SELECT id, %1 FROM %2 ORDER BY id").arg(displayColumn, fkTable);
            else
                query = QString("SELECT id FROM %1 ORDER BY id").arg(fkTable);

            QJsonArray fkData = db.doGet(query);

            for (const QJsonValue &val : fkData) {
                QJsonObject obj = val.toObject();
                QString idValue = obj.value("id").toVariant().toString();
                QString displayText;

                if (!displayColumn.isEmpty())
                    displayText = obj.value(displayColumn).toString();
                else
                    displayText = idValue; // fallback si no hay nombre/descripcion

                combo->addItem(displayText, idValue);
            }

            campoWidget = combo;
        } else {
            // Input normal
            auto *line = new QLineEdit;
            line->setPlaceholderText("Ingrese " + nombreCol);
            line->setStyleSheet(R"(
                QLineEdit {
                    border:1px solid #cbd5e1;
                    border-radius:6px;
                    padding:6px;
                    background-color:#f8fafc;
                    color:#1e293b;
                }
                QLineEdit:focus {
                    border:1.5px solid #2563eb;
                }
            )");
            campoWidget = line;
        }

        gridLayout->addWidget(label,row,col*2);
        gridLayout->addWidget(campoWidget,row,col*2+1);

        campos[nombreCol] = campoWidget;

        col++;
        if(col>1){
            col=0;
            row++;
        }
    }
}

void RegistroModal::guardarRegistro()
{
    QJsonObject nuevoRegistro;
    for (auto it = campos.begin(); it != campos.end(); ++it) {
        QString colName = it.key();
        QWidget *w = it.value();
        if (auto *line = qobject_cast<QLineEdit*>(w)) {
            nuevoRegistro[colName] = line->text();
        } else if (auto *combo = qobject_cast<QComboBox*>(w)) {
            nuevoRegistro[colName] = combo->currentData().toString();
        }
    }

    DatabaseManager db;
    if (db.doInsert(nombreTabla, nuevoRegistro)) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Éxito");
        msgBox.setText("Registro guardado correctamente.");
        msgBox.setIcon(QMessageBox::Information);

        // 🖤 Estilo oscuro
        msgBox.setStyleSheet(R"(
            QMessageBox {
                background-color: #111;
                color: #fff;
                border-radius: 10px;
            }
            QLabel {
                color: #fff;
                font-size: 14px;
            }
            QPushButton {
                background-color: #2563eb;
                color: white;
                border: none;
                border-radius: 6px;
                padding: 6px 14px;
                font-weight: 600;
            }
            QPushButton:hover {
                background-color: #1d4ed8;
            }
        )");

        msgBox.exec();
        accept();
    } else {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("No se pudo guardar el registro.");
        msgBox.setIcon(QMessageBox::Warning);

        // 🖤 Estilo oscuro
        msgBox.setStyleSheet(R"(
            QMessageBox {
                background-color: #111;
                color: #fff;
                border-radius: 10px;
            }
            QLabel {
                color: #fff;
                font-size: 14px;
            }
            QPushButton {
                background-color: #dc2626;
                color: white;
                border: none;
                border-radius: 6px;
                padding: 6px 14px;
                font-weight: 600;
            }
            QPushButton:hover {
                background-color: #b91c1c;
            }
        )");

        msgBox.exec();
    }
}
