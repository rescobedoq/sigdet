#include "donacion.h"
#include "ui_Donacion.h"

Donacion::Donacion(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Donacion)
{
    ui->setupUi(this);
}

Donacion::~Donacion()
{
    delete ui;
}
