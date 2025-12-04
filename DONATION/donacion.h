#ifndef DONACION_H
#define DONACION_H

#include <string>
#include "DonacionInvalidaException.h"

class Donacion {
protected:
    std::string tipo;
    std::string fecha;
    std::string donante;

public:
    Donacion(const std::string& tipo,
             const std::string& fecha,
             const std::string& donante)
        : tipo(tipo), fecha(fecha), donante(donante) {}

    virtual ~Donacion() = default;

    std::string getTipo() const { return tipo; }
    std::string getFecha() const { return fecha; }
    std::string getDonante() const { return donante; }

    virtual std::string info() const = 0; // método polimórfico
};

#endif
