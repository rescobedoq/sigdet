#ifndef DONACIONEQUIPOMEDICO_H
#define DONACIONEQUIPOMEDICO_H

#include "donacion.h"

class DonacionEquipoMedico : public Donacion {
private:
    std::string equipo;  // camilla, mascarillas, botiquín, etc.
    int cantidad;

public:
    DonacionEquipoMedico(const std::string& fecha,
                         const std::string& donante,
                         const std::string& equipo,
                         int cantidad);

    std::string info() const override;
};

#endif
