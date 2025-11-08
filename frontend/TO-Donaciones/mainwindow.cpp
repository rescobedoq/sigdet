#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "sidebar.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Sidebar *sidebar = new Sidebar(this);
    QWidget *central = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(central);

    layout->addWidget(sidebar);
    layout->addStretch(); // donde irá el resto del contenido

    setCentralWidget(central);
}

MainWindow::~MainWindow()
{
    delete ui;
}
