#include "sidebar.h"
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
#include "iconhelper.h"

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
        "Dashboard", "Donaciones", "Inventario", "Donantes", "Informes", "Configuracion"
    };

    QButtonGroup *group = new QButtonGroup(this);
    group->setExclusive(true);

    for (const QString &item : items) {
        QPushButton *btn = new QPushButton(item);
        btn->setCheckable(true);

        iconhelper::setToggleIcon(btn, ":/icons/sidebar/" + item.toLower() + ".svg");

        menu->addWidget(btn);
        group->addButton(btn);
    }

    // Opcional: marcar uno por defecto
    if (QAbstractButton *firstBtn = group->buttons().value(0)) {
        firstBtn->setChecked(true);
    }

    // --- Pie (Ayuda / Cerrar sesión) ---
    auto *footer = new QVBoxLayout;
    QStringList footerItems = {"Ayuda", "Cerrar Sesion"};
    for (const QString &item : footerItems) {
        QPushButton *btn = new QPushButton(item);
        btn->setIcon(QIcon(":/icons/sidebar/" + item.toLower() + ".png"));
        btn->setIconSize(QSize(20, 20));
        footer->addWidget(btn);
    }
    footer->addStretch();

    // --- Ensamblar layout principal ---
    mainLayout->addLayout(header);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(menu);
    mainLayout->addStretch();
    mainLayout->addLayout(footer);
}
