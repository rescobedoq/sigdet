#include "donaciondinero.h"

DonacionDinero::DonacionDinero(const std::string& fecha,
                               const std::string& donante,
                               double monto,
                               const std::string& moneda)
    : Donacion("Dinero", fecha, donante),
    monto(monto), moneda(moneda) {}

std::string DonacionDinero::info() const {
    return "Donación monetaria: " + std::to_string(monto) + " " + moneda;
}
