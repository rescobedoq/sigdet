#include "donacionequipomedico.h"

DonacionEquipoMedico::DonacionEquipoMedico(const std::string& fecha,
                                           const std::string& donante,
                                           const std::string& equipo,
                                           int cantidad)
    : Donacion("Equipo Médico", fecha, donante),
    equipo(equipo), cantidad(cantidad) {}

std::string DonacionEquipoMedico::info() const {
    return "Equipo médico: " + equipo +
           " Cantidad: " + std::to_string(cantidad);
}
