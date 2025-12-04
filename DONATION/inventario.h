#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <vector>
#include <memory>
#include "donacionbase.h"

class Inventario {
private:
    std::vector<std::shared_ptr<DonacionBase>> donaciones;
    int ultimoID = 0;

public:
    void agregarDonacion(std::shared_ptr<DonacionBase> donacion);
    void listarDonaciones() const;
    std::shared_ptr<DonacionBase> buscarDonacion(int id) const;
    bool eliminarDonacion(int id);
};

#endif
