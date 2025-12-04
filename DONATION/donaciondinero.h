#ifndef DONACIONDINERO_H
#define DONACIONDINERO_H

#include "donacion.h"

class DonacionDinero : public Donacion {
private:
    double monto;
    std::string moneda;

public:
    DonacionDinero(const std::string& fecha,
                   const std::string& donante,
                   double monto,
                   const std::string& moneda);

    std::string info() const override;
};

#endif
