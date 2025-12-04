#ifndef DONACIONMUEBLE_H
#define DONACIONMUEBLE_H

#include "donacion.h"

class DonacionMueble : public Donacion {
private:
    std::string descripcion; // cama, mesa, silla, etc.
    bool buenEstado;

public:
    DonacionMueble(const std::string& fecha,
                   const std::string& donante,
                   const std::string& descripcion,
                   bool buenEstado);

    std::string info() const override;
};

#endif
