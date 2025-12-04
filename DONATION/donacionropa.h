#ifndef DONACIONROPA_H
#define DONACIONROPA_H

#include "donacion.h"

class DonacionRopa : public Donacion {
private:
    std::string tipoRopa;   // invierno, verano, interior, etc.
    std::string talla;      // S, M, L, XL, niño, adulto
    bool buenEstado;

public:
    DonacionRopa(const std::string& fecha,
                 const std::string& donante,
                 const std::string& tipoRopa,
                 const std::string& talla,
                 bool buenEstado);

    std::string info() const override;
};

#endif
