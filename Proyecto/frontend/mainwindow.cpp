#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "sidebarView.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QStackedWidget>
#include "inventarioView.h"
#include "donacionesrecibidasView.h"
#include "donacionesenviadasView.h"
#include "donantesView.h"
#include "beneficiarioView.h"
#include "informesView.h"
#include "ayudaView.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sidebar = new Sidebar(this);
    QWidget *central = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(central);

    // --- Crear área de contenido dinámico ---
    stackedWidget = new QStackedWidget;

    // Ejemplo: agregar 3 vistas (puedes reemplazar por tus clases reales)
    QWidget *dashboardView = new QWidget;
    dashboardView->setStyleSheet("background-color: #f6f6f8;");
    auto *dashLayout = new QVBoxLayout(dashboardView);
    dashLayout->addWidget(new QLabel("🏠 Dashboard"));

    QWidget *donacionesView = new QWidget;
    donacionesView->setStyleSheet("background-color: #f6f6f8;");
    auto *donLayout = new QVBoxLayout(donacionesView);
    donLayout->addWidget(new QLabel("💰 Donaciones"));

    stackedWidget->addWidget(new DonacionesRecibidasView); // index 0
    stackedWidget->addWidget(new DonacionesEnviadasView); // index 1
    stackedWidget->addWidget(new InventarioView); // index 2
    stackedWidget->addWidget(new DonantesView); // index 3
    stackedWidget->addWidget(new BeneficiarioView); // index 4
    stackedWidget->addWidget(new InformesView); // index 5
    stackedWidget->addWidget(new AyudaView); // index 6
    // --- Componer el layout principal ---
    layout->addWidget(sidebar);
    layout->addWidget(stackedWidget, 1);

    setCentralWidget(central);
    setStyleSheet(R"(
        QMainWindow {
            background-color: #f6f6f8;
            border: none;
            margin: 0;
            padding: 0;
        }
    )");

    // --- Conectar el Sidebar ---
    connect(sidebar, &Sidebar::menuSelected, this, &MainWindow::onMenuSelected);

    // Mostrar la vista inicial
    stackedWidget->setCurrentIndex(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onMenuSelected(const QString &menuName)
{
    auto recreateView = [&](int index, QWidget *newView) {
        QWidget *oldWidget = stackedWidget->widget(index);
        if (oldWidget) {
            stackedWidget->removeWidget(oldWidget);
            oldWidget->deleteLater();
        }
        stackedWidget->insertWidget(index, newView);
        stackedWidget->setCurrentIndex(index);
    };

    if (menuName == "Donaciones Recibidas") {
        recreateView(0, new DonacionesRecibidasView);
    }
    else if (menuName == "Donaciones Enviadas") {
        recreateView(1, new DonacionesEnviadasView);
    }
    else if (menuName == "Inventario") {
        recreateView(2, new InventarioView);
    }
    else if (menuName == "Donantes") {
        recreateView(3, new DonantesView);
    }
    else if (menuName == "Beneficiarios") {
        recreateView(4, new BeneficiarioView);
    }
    else if (menuName == "Informes") {
        recreateView(5, new InformesView);
    }
    else if (menuName == "Ayuda") {
        recreateView(6, new AyudaView);
    }
    else if (menuName == "Cerrar Sesion") {
        this->hide();  // Oculta el panel de control
        emit logoutRequested();  // 🔹 Señal que informará al main que se hizo logout
    }
}
void MainWindow::resetToDefaultView()
{
    if (stackedWidget)
        stackedWidget->setCurrentIndex(0);  // Vuelve a Donaciones Recibidas

    if (sidebar)
        sidebar->resetToDefault();           // Marca el primer botón
}
