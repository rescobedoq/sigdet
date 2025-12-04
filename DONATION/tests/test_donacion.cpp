#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../Headers Files/donacionbase.h"
#include "../Headers Files/inventario.h"

TEST_CASE("Crear una donación válida") {
    DonacionBase d("Ropa", "2024-01-01", 10);

    REQUIRE(d.getTipo() == "Ropa");
    REQUIRE(d.getFecha() == "2024-01-01");
    REQUIRE(d.getCantidad() == 10);
}

TEST_CASE("No permitir tipo vacío") {
    REQUIRE_THROWS_AS(DonacionBase("", "2024-01-01", 5), DonacionInvalidaException);
}

TEST_CASE("Agregar donación al inventario") {
    Inventario inv;

    shared_ptr<DonacionBase> d = make_shared<DonacionBase>("Alimento", "2024-01-02", 20);
    inv.agregarDonacion(d);

    REQUIRE(inv.listarCantidad() == 1);
}

TEST_CASE("Buscar donación por ID") {
    Inventario inv;

    auto d = make_shared<DonacionBase>("Libro", "2024-01-03", 3);
    inv.agregarDonacion(d);

    auto buscada = inv.buscarDonacion(1);
    REQUIRE(buscada != nullptr);
    REQUIRE(buscada->getTipo() == "Libro");
}

TEST_CASE("Eliminar donación") {
    Inventario inv;

    auto d = make_shared<DonacionBase>("Higiene", "2024-01-04", 4);
    inv.agregarDonacion(d);

    REQUIRE(inv.eliminarDonacion(1) == true);
    REQUIRE(inv.eliminarDonacion(1) == false); // ya no existe
}
