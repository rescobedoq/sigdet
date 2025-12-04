#include "donacionlibro.h"

DonacionLibro::DonacionLibro(const std::string& fecha,
                             const std::string& donante,
                             const std::string& titulo,
                             const std::string& categoria)
    : Donacion("Libro", fecha, donante),
    titulo(titulo), categoria(categoria) {}

std::string DonacionLibro::info() const {
    return "Libro: " + titulo + " (" + categoria + ")";
}
