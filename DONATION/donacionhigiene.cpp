#include "donacionhigiene.h"

DonacionHigiene::DonacionHigiene(const std::string& fecha,
                                 const std::string& donante,
                                 const std::string& producto,
                                 int cantidad)
    : Donacion("Higiene", fecha, donante),
    producto(producto), cantidad(cantidad) {}

std::string DonacionHigiene::info() const {
    return "Producto de higiene: " + producto +
           " Cantidad: " + std::to_string(cantidad);
}
