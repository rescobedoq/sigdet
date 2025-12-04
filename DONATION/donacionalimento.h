#ifndef DONACIONALIMENTO_H
#define DONACIONALIMENTO_H

#include "donacion.h"

class DonacionAlimento : public Donacion {
private:
    std::string categoria; // enlatado, pasta, arroz, bebida, etc.
    int cantidad;          // unidades
    std::string fechaVencimiento;

public:
    DonacionAlimento(const std::string& fecha,
                     const std::string& donante,
                     const std::string& categoria,
                     int cantidad,
                     const std::string& fechaVencimiento);

    std::string info() const override;
};

#endif
