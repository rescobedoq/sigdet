#include "donacion.h"
#include "./ui_donacion.h"

Donacion::Donacion(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Donacion)
{
    ui->setupUi(this);
}

Donacion::~Donacion()
{
    delete ui;
}