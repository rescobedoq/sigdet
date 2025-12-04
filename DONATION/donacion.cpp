#include "Donacion.h"

Donacion::Donacion(const std::string& tipo, const std::string& fecha, double cantidad)
    : tipo(tipo), fecha(fecha), cantidad(cantidad)
{
    if (tipo.empty()) {
        throw DonacionInvalidaException("El tipo de donación no puede estar vacío.");
    }

    if (fecha.empty()) {
        throw DonacionInvalidaException("La fecha no puede estar vacía.");
    }

    if (cantidad <= 0) {
        throw DonacionInvalidaException("La cantidad debe ser mayor que cero.");
    }
}

std::string Donacion::getTipo() const { return tipo; }
std::string Donacion::getFecha() const { return fecha; }
double Donacion::getCantidad() const { return cantidad; }

