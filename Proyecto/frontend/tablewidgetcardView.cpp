#include "tablewidgetcardView.h"
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include "iconhelperController.h"
TableWidgetCard::TableWidgetCard(const QString &title,
                                 const QJsonArray &data,
                                 const QString &categoryColumn,
                                 QWidget *parent,
                                 const QStringList &headers)
    : QWidget(parent),
    m_categoryColumn(categoryColumn),
    m_originalData(data)
{
    auto *card = new QFrame;
    card->setObjectName("card");
    card->setStyleSheet(R"(
        QTableWidget QLineEdit {
            background-color: black;
            color: white;
            border-radius: 4px;
        }
        QFrame#card {
            background-color: white;
            border: 1px solid #e5e7eb;
            border-radius: 12px;
        }
        QLabel.sectionTitle {
            font-size: 18px;
            font-weight: 700;
            color: #111318;
        }
        /* ---- Estilo corregido para QLineEdit ---- */
        QLineEdit#search {
            background-color: #f9fafb;
            border: 1px solid #d1d5db;
            border-radius: 8px;
            height: 38px;
            padding-left: 34px;
            font-size: 13px;
            color: #111318;
        }
        QLineEdit#search:focus {
            border: 1px solid #2563eb;
            background-color: #ffffff;
        }
        QPushButton.toolbar {
            border-radius: 8px;
            background: transparent;
            padding: 6px;
        }
        QPushButton.export {
            background: #e5e7eb;
            border-radius: 8px;
            padding: 6px 12px;
            font-weight: 600;
            color: #111318;
        }
        QPushButton.export:hover {
            background: #d1d5db; /* un poco más oscuro al pasar el mouse */
            color: #000000;      /* opcional, ajusta contraste */
        }

    )");

    auto *layout = new QVBoxLayout(card);
    layout->setContentsMargins(16, 14, 16, 14);
    layout->setSpacing(6);

    // --- Header ---
    QLabel *titleLabel = new QLabel(title);
    titleLabel->setProperty("class", "sectionTitle");
    layout->addWidget(titleLabel);

    // 🔹 Toolbar
    QHBoxLayout *toolbar = new QHBoxLayout;
    toolbar->setSpacing(8);

    // Buscador
    m_searchEdit = new QLineEdit;
    m_searchEdit->setObjectName("search");
    m_searchEdit->setPlaceholderText("Buscar...");
    m_searchEdit->setClearButtonEnabled(true);
    m_searchEdit->setFixedHeight(36);
    m_searchEdit -> setMaximumWidth(600);
    connect(m_searchEdit, &QLineEdit::textChanged, this, &TableWidgetCard::onSearchTextChanged);

    QAction *searchIcon = new QAction(QIcon(":/icons/generalIcons/search.svg"), "", m_searchEdit);
    m_searchEdit->addAction(searchIcon, QLineEdit::LeadingPosition);

    // 🔹 Estilo visual para parecerse al HTML Tailwind
    m_searchEdit->setStyleSheet(R"(
        QLineEdit#search {
            background-color: #f9fafb;
            border: 1px solid #d1d5db;
            border-radius: 8px;
            height: 36px;
            padding-left: 10px;      /* Espaciado entre ícono y texto */
            font-size: 13px;
            color: #111318;
        }
        QLineEdit#search:focus {
            border: 1px solid #2563eb;
            background-color: #ffffff;
        }
    )");

    toolbar->addWidget(m_searchEdit, 1);
    // --- Export ---
    QPushButton *exportBtn = new QPushButton("Exportar");
    exportBtn->setIcon(QIcon(":/icons/generalIcons/download.svg"));
    exportBtn->setMaximumWidth(110);
    exportBtn->setIconSize(QSize(20,20));
    exportBtn->setCursor(Qt::PointingHandCursor);
    exportBtn->setProperty("class", "export");
    connect(exportBtn, &QPushButton::clicked, this, &TableWidgetCard::onExportCsv);
    toolbar->addSpacing(40); // margen izquierdo de 15px
    toolbar->addWidget(exportBtn);

    layout->addLayout(toolbar);

    // --- Barra de filtros moderna con menús ---
    auto *filterBar = new QHBoxLayout;
    filterBar->setSpacing(8);
    filterBar->setContentsMargins(0, 0, 0, 4);

    // --- CONTENEDOR DE FILTRO CATEGORÍA ---
    QFrame *catContainer = new QFrame;
    auto *catLayout = new QHBoxLayout(catContainer);

    // --- BOTÓN CATEGORÍA ---
    QPushButton *categoriaBtn = new QPushButton;
    categoriaBtn->setCursor(Qt::PointingHandCursor);
    categoriaBtn->setFixedWidth(180);  // ✅ Aumenta el ancho mínimo

    categoriaBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    categoriaBtn->setStyleSheet(R"(
    QPushButton {
        background-color: #f9fafb;
        border: 1px solid #d1d5db;
        border-radius: 8px;
        padding: 6px 0px;
        font-size: 13px;
        color: #111318;
    }
    QPushButton:hover {
        background-color: #e5e7eb;
    }
)");

    // --- Layout interno para íconos y texto ---
    QHBoxLayout *catBtnLayout = new QHBoxLayout(categoriaBtn);

    // Icono categoría
    QLabel *iconCategory = new QLabel;
    iconCategory->setPixmap(QIcon(":/icons/tabla/category.svg").pixmap(16, 16));
    catBtnLayout->addWidget(iconCategory);

    // Texto
    m_catText  = new QLabel(categoryColumn);
    m_catText ->setStyleSheet("font-weight: 500; color: #374151;");
    catBtnLayout->addWidget(m_catText );

    // Icono expand_more
    QLabel *expandCat = new QLabel;
    expandCat->setPixmap(QIcon(":/icons/tabla/expand_more.svg").pixmap(16, 16));
    catBtnLayout->addWidget(expandCat);

    // Añadir el botón al layout
    catLayout->addWidget(categoriaBtn);

    // --- MENÚ de categorías ---
    QMenu *catMenu = new QMenu(categoriaBtn); // ✅ Establece padre
    QSet<QString> categorias;

    for (const auto &d : data) {
        QJsonObject obj = d.toObject();
        QJsonValue val = obj.value(categoryColumn);

        QString text;
        if (val.isString())
            text = val.toString();
        else if (val.isDouble())
            text = QString::number(val.toInt());
        else
            text = QString();

        if (!text.isEmpty())
            categorias.insert(text);
    }

    // Agregar acción "Todos"
    QAction *allAction = catMenu->addAction("Todos");
    connect(allAction, &QAction::triggered, this, [this]() {
        onFilterCategoryChanged("Todos");
    });

    // Agregar cada categoría
    for (const QString &c : categorias) {
        QAction *act = catMenu->addAction(c);
        connect(act, &QAction::triggered, this, [this, c]() {
            onFilterCategoryChanged(c);
        });
    }

    categoriaBtn->setMenu(catMenu);
    categoriaBtn->setStyleSheet(categoriaBtn->styleSheet() + R"(
    QPushButton::menu-indicator { image: none; }
)");

    // 🔹 Botón de fecha (abre calendario)
    // --- CONTENEDOR DE FILTRO FECHA ---
    QFrame *fechaContainer = new QFrame;
    auto *fechaLayout = new QHBoxLayout(fechaContainer);
    fechaLayout->setContentsMargins(0, 0, 0, 0);
    fechaLayout->setSpacing(6);

    // --- Botón de fecha (abre calendario) ---
    QPushButton *fechaBtn = new QPushButton;
    fechaBtn->setCursor(Qt::PointingHandCursor);
    fechaBtn->setMinimumWidth(130);  // ✅ Aumenta el ancho mínimo
    fechaBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    fechaBtn->setStyleSheet(R"(
    QPushButton {
        background-color: #f9fafb;
        border: 1px solid #d1d5db;
        border-radius: 8px;
        padding: 6px 12px;
        font-size: 13px;
        color: #111318;
    }
    QPushButton:hover {
        background-color: #e5e7eb;
    }
)");

    QHBoxLayout *fechaBtnLayout = new QHBoxLayout(fechaBtn);
    fechaBtnLayout->setContentsMargins(6, 2, 6, 2);
    fechaBtnLayout->setSpacing(6);

    QLabel *iconCalendar = new QLabel;
    iconCalendar->setPixmap(QIcon(":/icons/tabla/calendar_month.svg").pixmap(16, 16));
    fechaBtnLayout->addWidget(iconCalendar);

    m_fechaText = new QLabel("Fecha");
    m_fechaText->setStyleSheet("font-weight: 500; color: #374151;");
    fechaBtnLayout->addWidget(m_fechaText);

    QLabel *expandIcon = new QLabel;
    expandIcon->setPixmap(QIcon(":/icons/tabla/expand_more.svg").pixmap(16, 16));
    fechaBtnLayout->addWidget(expandIcon);

    fechaLayout->addWidget(fechaBtn);

    // --- Conectar clic para mostrar calendario ---
    connect(fechaBtn, &QPushButton::clicked, this, [=]() {
        QDialog *calendarDialog = new QDialog(this);
        calendarDialog->setWindowFlags(Qt::Popup);
        calendarDialog->setStyleSheet(R"(
        QDialog {
            border: 1px solid #d1d5db;
            border-radius: 12px;
            background: white;
        }
        QCalendarWidget QAbstractItemView {
            selection-background-color: #2563eb;
            outline: none;
        }
    )");

        QVBoxLayout *dialogLayout = new QVBoxLayout(calendarDialog);
        dialogLayout->setContentsMargins(8, 8, 8, 8);

        QCalendarWidget *calendar = new QCalendarWidget(calendarDialog);
        calendar->setGridVisible(true);
        dialogLayout->addWidget(calendar);

        connect(calendar, &QCalendarWidget::clicked, this, [=](const QDate &date) {
            onFilterDateChanged(date);
            calendarDialog->accept();
        });

        QPoint pos = fechaBtn->mapToGlobal(QPoint(0, fechaBtn->height()));
        calendarDialog->move(pos);
        calendarDialog->exec();
    });


    // 🔹 Botón para borrar filtros (solo ícono)
    QPushButton *clearFiltersBtn = new QPushButton;
    clearFiltersBtn->setCursor(Qt::PointingHandCursor);
    clearFiltersBtn->setToolTip("Borrar filtros");
    clearFiltersBtn->setIcon(QIcon(":/icons/generalIcons/refresh.svg")); // Ruta a tu SVG
    clearFiltersBtn->setIconSize(QSize(18, 18)); // Tamaño del ícono
    clearFiltersBtn->setFixedSize(22, 22);       // Tamaño total del botón (ligeramente más grande que el ícono)
    clearFiltersBtn->setStyleSheet(R"(
    QPushButton {
        background: transparent;
        border: none;
        padding: 0;
        margin: 0;
    }
    QPushButton:hover {
        background-color: rgba(0, 0, 0, 0.05);
        border-radius: 6px;
    }
)");

    connect(clearFiltersBtn, &QPushButton::clicked, this, [this]() {
        // 🔹 Restablece los filtros
        m_currentCategory = "Todos";
        m_currentDate.clear();

        // 🔹 Actualiza los textos visibles
        if (m_catText)
            m_catText->setText("Categoría");
        if (m_fechaText)
            m_fechaText->setText("Fecha");

        // 🔹 Muestra todas las filas
        for (int i = 0; i < m_table->rowCount(); ++i)
            m_table->setRowHidden(i, false);
    });


    // --- Añadir al layout principal ---
    filterBar->addWidget(catContainer);
    filterBar->addWidget(fechaContainer);
    filterBar->addWidget(clearFiltersBtn);
    filterBar->addStretch();
    layout->addLayout(toolbar);
    layout->addLayout(filterBar);

    // --- Table ---
    m_table = new QTableWidget(data.size(), data[0].toObject().keys().size());
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_table->horizontalHeader()->setStretchLastSection(false);

    m_table->verticalHeader()->hide();
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setShowGrid(false);
    m_table->setAlternatingRowColors(false); // 🔹 Todas las filas del mismo color

    // ---- Estilo corregido para fondo homogéneo gris claro ----
    m_table->setStyleSheet(R"(
        QHeaderView::section {
            background-color: #f9fafb;          /* bg-gray-50 */
            color: #374151;                     /* text-gray-700 */
            text-transform: uppercase;          /* uppercase */
            font-weight: bold;                  /* negrita */
            font-size: 12px;                    /* text-xs */
            padding: 10px 12px;                 /* px-6 py-3 */
            text-align: left;                   /* alineado a la izquierda */
            border: none;
            border-bottom: 1px solid #e5e7eb;   /* border-gray-200 */
        }
        QHeaderView::section:horizontal {
            border-top-left-radius: 6px;
            border-top-right-radius: 6px;
        }
        QTableWidget {
            background-color: #ffffff;
            gridline-color: #e5e7eb;
        }
        QTableWidget::item {
            background-color: #ffffff;
            color: #111318;
            padding: 8px;
            font-size: 13px;
        }
        QTableWidget::item:selected {
            background-color: #dbeafe;          /* azul claro de selección */
        }
    )");
    layout->addWidget(m_table, /*stretch*/ 1);

    // Cargar datos
    loadTable(data,headers);

    // Agregar tarjeta al layout principal
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(card);
}

void TableWidgetCard::loadTable(const QJsonArray &data, const QStringList &receivedHeaders)
{
    if (data.isEmpty() || receivedHeaders.isEmpty())
        return;

    QStringList headers = receivedHeaders;
    headers << "Acciones"; // 👈 Agregar aquí, NO dentro de setupTableHeaders()

    setupTableHeaders(headers, data.size());

    for (int row = 0; row < data.size(); ++row) {
        const QJsonObject obj = data[row].toObject();
        populateRow(row, obj, headers); // 👈 Pasa headers con "Acciones"
    }
}
// --------------------------------------------------------
// Configura columnas, encabezados y comportamiento general
// --------------------------------------------------------
void TableWidgetCard::setupTableHeaders(const QStringList &headers, int rowCount)
{
    m_table->setEditTriggers(QAbstractItemView::DoubleClicked |
                             QAbstractItemView::SelectedClicked |
                             QAbstractItemView::EditKeyPressed);

    m_table->setColumnCount(headers.size());
    m_table->setHorizontalHeaderLabels(headers);
    m_table->setRowCount(rowCount);
    m_table->horizontalHeader()->setStretchLastSection(true);
}

// --------------------------------------------------------
// Llena una fila de la tabla con los datos del JSON
// --------------------------------------------------------
void TableWidgetCard::populateRow(int row, const QJsonObject &obj, const QStringList &headers)
{
    for (int col = 0; col < headers.size(); ++col) {
        if (col == headers.size() - 1)
            break; // última columna = botones

        QString key = headers[col];
        QString val = obj.value(key).toVariant().toString();

        auto *item = new QTableWidgetItem(val);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        m_table->setItem(row, col, item);
    }

    // Crea los botones de acción
    QWidget *actions = createActionButtons(row, obj, headers, false);
    m_table->setCellWidget(row, headers.size() - 1, actions);
}

// --------------------------------------------------------
// Crea los botones de acción (editar / eliminar / confirmar / cancelar)
// --------------------------------------------------------
QWidget *TableWidgetCard::createActionButtons(int row, const QJsonObject &obj, const QStringList &headers, bool editing)
{
    QWidget *actionWidget = new QWidget;
    auto *hl = new QHBoxLayout(actionWidget);
    hl->setContentsMargins(0, 0, 0, 0);
    hl->setSpacing(6);
    hl->setAlignment(Qt::AlignCenter);

    if (!editing) {
        QPushButton *editBtn = createIconButton(":/icons/tabla/edit.svg", "Editar", QColor("#EAB308"));
        QPushButton *deleteBtn = createIconButton(":/icons/tabla/delete.svg", "Eliminar", QColor("#dc2626"));

        hl->addWidget(editBtn);
        hl->addWidget(deleteBtn);

        connect(editBtn, &QPushButton::clicked, this, [=]() {
            enableRowEditing(row, headers);
            m_table->setCellWidget(row, headers.size() - 1, createActionButtons(row, obj, headers, true));
            m_table->editItem(m_table->item(row, 0)); // iniciar edición
        });

        connect(deleteBtn, &QPushButton::clicked, this, [=]() {
            qDebug() << "Row:" << row << "OBJ:" << obj;
            QString id = obj["id"].isString()
                             ? obj["id"].toString()
                             : QString::number(obj["id"].toInt());
            emit actionTriggered(id, "eliminar");
        });
    } else {
        QPushButton *confirmBtn = createIconButton(":/icons/tabla/save.svg", "Confirmar", QColor("#135bec"));
        QPushButton *cancelBtn  = createIconButton(":/icons/tabla/cancel.svg", "Cancelar", QColor("#dc2626"));

        hl->addWidget(confirmBtn);
        hl->addWidget(cancelBtn);

        connect(confirmBtn, &QPushButton::clicked, this, [=]() {
            confirmRowEdit(row, obj, headers);
        });

        connect(cancelBtn, &QPushButton::clicked, this, [=]() {
            cancelRowEdit(row, obj, headers);
        });
    }

    return actionWidget;
}

// --------------------------------------------------------
// Crea un botón de icono con color y tooltip
// --------------------------------------------------------
QPushButton *TableWidgetCard::createIconButton(const QString &iconPath, const QString &tooltip, const QColor &hoverColor)
{
    QPushButton *btn = new QPushButton;
    btn->setCursor(Qt::PointingHandCursor);
    btn->setToolTip(tooltip);
    btn->setFixedSize(16, 16);
    btn->setIcon(IconHelper::recolorSvg(iconPath, hoverColor, QSize(16, 16)));
    btn->setStyleSheet(QString(R"(
        QPushButton {
            background-color: transparent;
            border: none;
            border-radius: 6px;
        }
        QPushButton:hover {
            background-color: rgba(%1,%2,%3,0.1);
        }
    )").arg(hoverColor.red()).arg(hoverColor.green()).arg(hoverColor.blue()));
    return btn;
}

// --------------------------------------------------------
// Activa la edición en una fila
// --------------------------------------------------------
void TableWidgetCard::enableRowEditing(int row, const QStringList &headers)
{
    for (int c = 0; c < headers.size() - 1; ++c)
        m_table->item(row, c)->setFlags(m_table->item(row, c)->flags() | Qt::ItemIsEditable);
}

// --------------------------------------------------------
// Confirma los cambios en la fila y emite señal con datos nuevos
// --------------------------------------------------------
void TableWidgetCard::confirmRowEdit(int row, const QJsonObject &obj, const QStringList &headers)
{
    QJsonObject updatedObj;
    for (int c = 0; c < headers.size() - 1; ++c) {
        QString key = headers[c];
        QString val = m_table->item(row, c)->text();
        updatedObj[key] = val;
        m_table->item(row, c)->setFlags(m_table->item(row, c)->flags() & ~Qt::ItemIsEditable);
    }

    QString id = obj["id"].isString()
                     ? obj["id"].toString()
                     : QString::number(obj["id"].toInt());

    emit actionTriggeredWithData(id, "confirmar", updatedObj);
    m_table->setCellWidget(row, headers.size() - 1, createActionButtons(row, obj, headers, false));
}

// --------------------------------------------------------
// Cancela la edición y restaura los valores originales
// --------------------------------------------------------
void TableWidgetCard::cancelRowEdit(int row, const QJsonObject &, const QStringList &headers)
{
    if (row < 0 || row >= m_currentData.size())
        return;

    QJsonObject obj = m_currentData[row].toObject(); // 🔹 Datos actuales

    for (int c = 0; c < headers.size() - 1; ++c) {
        QString key = headers[c];
        m_table->item(row, c)->setText(obj.value(key).toString());
        m_table->item(row, c)->setFlags(m_table->item(row, c)->flags() & ~Qt::ItemIsEditable);
    }

    m_table->setCellWidget(row, headers.size() - 1, createActionButtons(row, obj, headers, false));
}
void TableWidgetCard::onSearchTextChanged(const QString &text)
{
    for (int i = 0; i < m_table->rowCount(); ++i) {
        bool visible = false;
        for (int j = 0; j < m_table->columnCount(); ++j) {
            auto *item = m_table->item(i, j);
            if (item && item->text().contains(text, Qt::CaseInsensitive)) {
                visible = true;
                break;
            }
        }
        m_table->setRowHidden(i, !visible);
    }
}
void TableWidgetCard::onExportCsv()
{
    QString path = QFileDialog::getSaveFileName(this, "Exportar inventario", QString(), "CSV files (*.csv)");
    if (path.isEmpty()) return;
    exportTableToCsv(path);
}

void TableWidgetCard::exportTableToCsv(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Cannot open file for writing:" << filePath;
        return;
    }
    QTextStream out(&file);

    // Header
    QStringList headers;
    for (int c = 0; c < m_table->columnCount() - 1; ++c) { // omit actions column
        headers << m_table->horizontalHeaderItem(c)->text();
    }
    out << headers.join(',') << '\n';

    // Rows
    for (int r = 0; r < m_table->rowCount(); ++r) {
        if (m_table->isRowHidden(r)) continue; // export only visible rows
        QStringList rowValues;
        for (int c = 0; c < m_table->columnCount() - 1; ++c) {
            QTableWidgetItem *it = m_table->item(r, c);
            rowValues << (it ? it->text() : QString());
        }
        out << rowValues.join(',') << '\n';
    }
    file.close();
}

void TableWidgetCard::onFilterCategoryChanged(const QString &category)
{
    if (!m_table)
        return;

    if (m_catText)
        m_catText->setText(m_categoryColumn+": " + category);

    m_currentCategory = category;
    applyFilters();
}
void TableWidgetCard::onFilterDateChanged(const QDate &date)
{
    if (!m_table)
        return;

    QString dateStr = date.toString("yyyy-MM-dd"); // mismo formato que la tabla

    if (m_fechaText)
        m_fechaText->setText(date.toString("dd/MM/yyyy"));

    m_currentDate = dateStr;
    applyFilters();
}

void TableWidgetCard::applyFilters()
{
    if (!m_table)
        return;

    int colCat = -1;
    int colDate = -1;

    for (int i = 0; i < m_table->columnCount(); ++i) {
        QString header = m_table->horizontalHeaderItem(i)->text();
        if (header == m_categoryColumn)
            colCat = i;
        else if (header.contains("Fecha", Qt::CaseInsensitive))
            colDate = i;


    }

    if (colCat == -1 || colDate == -1)
        return;

    for (int i = 0; i < m_table->rowCount(); ++i) {
        QTableWidgetItem *catItem = m_table->item(i, colCat);
        QTableWidgetItem *dateItem = m_table->item(i, colDate);

        bool catMatch = (m_currentCategory == "Todos") ||
                        (catItem && catItem->text() == m_currentCategory);

        bool dateMatch = (m_currentDate.isEmpty()) ||
                         (dateItem && dateItem->text().startsWith(m_currentDate));

        m_table->setRowHidden(i, !(catMatch && dateMatch));
    }
}

void TableWidgetCard::reloadData(const QJsonArray &newData, const QStringList &headers)
{
    m_currentData = newData; // 🔹 Mantén copia actual
    // Limpia la tabla actual
    m_table->clearContents();
    m_table->setRowCount(0);

    if (newData.isEmpty() || headers.isEmpty())
        return;

    // Añade nuevamente la columna "Acciones"
    QStringList fullHeaders = headers;
    fullHeaders << "Acciones";

    // Vuelve a configurar los encabezados
    setupTableHeaders(fullHeaders, newData.size());

    // Llena la tabla con los nuevos datos
    for (int row = 0; row < newData.size(); ++row) {
        const QJsonObject obj = newData[row].toObject();
        populateRow(row, obj, fullHeaders);
    }

    // Forzar refresco visual
    m_table->viewport()->update();
}
