#include "donacionropa.h"

DonacionRopa::DonacionRopa(const std::string& fecha,
                           const std::string& donante,
                           const std::string& tipoRopa,
                           const std::string& talla,
                           bool buenEstado)
    : Donacion("Ropa", fecha, donante),
    tipoRopa(tipoRopa), talla(talla), buenEstado(buenEstado) {}

std::string DonacionRopa::info() const {
    return "Ropa: " + tipoRopa + " Talla: " + talla +
           (buenEstado ? " (Buen estado)" : " (Mal estado)");
}
