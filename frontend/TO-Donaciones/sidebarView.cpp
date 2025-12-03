#include "sidebarView.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QIcon>
#include <QButtonGroup>

#include <QFile>
#include <QSvgRenderer>
#include <QPainter>
#include <QPixmap>
#include "iconhelperController.h"

Sidebar::Sidebar(QWidget *parent)
    : QFrame(parent)
{
    setFixedWidth(240);
    setStyleSheet(R"(
        QFrame {
            background-color: #ffffff;
            border-right: 1px solid #e5e7eb;
        }
        QLabel {
            color: #111318;
        }
        QPushButton {
            text-align: left;
            padding: 8px 12px;
            border-radius: 8px;
            color: #616f89;
            font-weight: 500;
        }
        QPushButton:hover {
            background-color: #f1f5f9;
        }
        QPushButton:checked {
            background-color: #e0ecff;
            color: #2563eb;
        }
    )");

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(16, 16, 16, 16);
    mainLayout->setSpacing(12);

    // --- Encabezado con logo y texto ---
    auto *header = new QHBoxLayout;
    auto *logo = new QLabel;
    QPixmap logoPix(":/icons/sidebar/logo.png");
    logo->setPixmap(logoPix.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logo->setFixedSize(80, 80);
    logo->setStyleSheet("border-radius: 20px;");

    auto *titleBox = new QVBoxLayout;
    auto *name = new QLabel("ONG Peru");
    name->setStyleSheet("font-size: 14px; font-weight: bold; color: #111318;");
    auto *subtitle = new QLabel("Panel Administrativo");
    subtitle->setStyleSheet("font-size: 12px; color: #616f89;");
    titleBox->addWidget(name);
    titleBox->addWidget(subtitle);

    header->addWidget(logo);
    header->addLayout(titleBox);
    header->addStretch();

    // --- Menú principal ---
    auto *menu = new QVBoxLayout;
    QStringList items = {
        "Donaciones Recibidas","Donaciones Enviadas", "Inventario", "Donantes", "Beneficiarios", "Informes"
    };

    QButtonGroup *group = new QButtonGroup(this);
    group->setExclusive(true);

    auto createMenuButton = [this, group](const QString &item) {
        QPushButton *btn = new QPushButton(item);
        btn->setCheckable(true);

        IconHelper::setToggleIcon(
            btn,
            ":/icons/sidebar/" + item.toLower() + ".svg",
            QColor(37, 99, 235),
            QColor(227, 227, 227),
            QSize(20, 20),
            [this, item](bool checked) {
                if (checked)
                    emit menuSelected(item);
            }
            );

        group->addButton(btn);
        return btn;
    };

    // Crear los botones del menú principal
    for (const QString &item : items) {
        QPushButton *btn = createMenuButton(item);
        menu->addWidget(btn);
    }

    // --- Pie (Ayuda / Cerrar sesión) ---
    auto *footer = new QVBoxLayout;

    // ✅ "Ayuda" también es parte del grupo y tiene toggle visual
    QPushButton *helpBtn = createMenuButton("Ayuda");
    footer->addWidget(helpBtn);

    // 🚫 "Cerrar Sesión" no se incluye en el grupo
    QPushButton *logoutBtn = createMenuButton("Cerrar Sesion");
    footer->addWidget(logoutBtn);

    footer->addStretch();

    // --- Ensamblar layout principal ---
    mainLayout->addLayout(header);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(menu);
    mainLayout->addStretch();
    mainLayout->addLayout(footer);

    // --- Marcar uno por defecto ---
    if (QAbstractButton *firstBtn = group->buttons().value(0)) {
        firstBtn->setChecked(true);
    }
}
void Sidebar::resetToDefault()
{
    // Busca el primer botón del grupo (Donaciones Recibidas) y lo marca como activo
    QList<QAbstractButton*> buttons = findChildren<QAbstractButton*>();
    if (!buttons.isEmpty()) {
        for (auto *btn : buttons)
            btn->setChecked(false); // desmarcar todo

        QAbstractButton *first = buttons.first();
        first->setChecked(true);
        emit menuSelected(first->text()); // 🔹 fuerza mostrar la vista inicial
    }
}
