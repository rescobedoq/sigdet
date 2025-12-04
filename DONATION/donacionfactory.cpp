#include "DonacionFactory.h"
#include "DonacionAlimento.h"
#include "DonacionRopa.h"

std::unique_ptr<Donacion> DonacionFactory::crearDonacion(
    const std::string& tipo, const std::string& fecha, double cantidad)
{
    if (tipo == "Alimento") return std::make_unique<DonacionAlimento>(fecha, cantidad);
    if (tipo == "Ropa")     return std::make_unique<DonacionRopa>(fecha, cantidad);

    throw std::runtime_error("Tipo de donación no válido");
}
