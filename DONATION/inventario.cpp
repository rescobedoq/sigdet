#include "inventario.h"
#include <iostream>

using namespace std;

void Inventario::agregarDonacion(shared_ptr<DonacionBase> donacion) {
    donacion->setID(++ultimoID);
    donaciones.push_back(donacion);
}

void Inventario::listarDonaciones() const {
    if (donaciones.empty()) {
        cout << "No hay donaciones registradas.\n";
        return;
    }

    for (auto &d : donaciones) {
        d->mostrar();
        cout << "------------------------\n";
    }
}

shared_ptr<DonacionBase> Inventario::buscarDonacion(int id) const {
    for (auto &d : donaciones)
        if (d->getID() == id)
            return d;
    return nullptr;
}

bool Inventario::eliminarDonacion(int id) {
    for (size_t i = 0; i < donaciones.size(); i++) {
        if (donaciones[i]->getID() == id) {
            donaciones.erase(donaciones.begin() + i);
            return true;
        }
    }
    return false;
}
