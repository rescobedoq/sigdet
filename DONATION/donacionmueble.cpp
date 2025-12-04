#include "donacionmueble.h"

DonacionMueble::DonacionMueble(const std::string& fecha,
                               const std::string& donante,
                               const std::string& descripcion,
                               bool buenEstado)
    : Donacion("Mueble", fecha, donante),
    descripcion(descripcion), buenEstado(buenEstado) {}

std::string DonacionMueble::info() const {
    return "Mueble: " + descripcion +
           (buenEstado ? " (Buen estado)" : " (Mal estado)");
}
