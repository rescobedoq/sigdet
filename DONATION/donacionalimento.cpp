#include "donacionalimento.h"

DonacionAlimento::DonacionAlimento(const std::string& fecha,
                                   const std::string& donante,
                                   const std::string& categoria,
                                   int cantidad,
                                   const std::string& fechaVencimiento)
    : Donacion("Alimento", fecha, donante),
    categoria(categoria), cantidad(cantidad),
    fechaVencimiento(fechaVencimiento) {}

std::string DonacionAlimento::info() const {
    return "Alimento: " + categoria + " Cantidad: " + std::to_string(cantidad) +
           " Vence: " + fechaVencimiento;
}
