#ifndef DONACIONFACTORY_H
#define DONACIONFACTORY_H

#include <string>
#include "donacion.h"
#include "donacionropa.h"
#include "donacionalimento.h"
#include "donacionhigiene.h"
#include "donacionmueble.h"
#include "donacionlibro.h"
#include "donacionequipomedico.h"
#include "donaciondinero.h"

class DonacionFactory {
public:
    static Donacion* crearDonacion(const std::string& tipo,
                                   const std::string& descripcion,
                                   int cantidad)
    {
        if (tipo == "ropa")
            return new DonacionRopa(descripcion, cantidad);

        else if (tipo == "alimento")
            return new DonacionAlimento(descripcion, cantidad);

        else if (tipo == "higiene")
            return new DonacionHigiene(descripcion, cantidad);

        else if (tipo == "mueble")
            return new DonacionMueble(descripcion, cantidad);

        else if (tipo == "libro")
            return new DonacionLibro(descripcion, cantidad);

        else if (tipo == "equipomedico")
            return new DonacionEquipoMedico(descripcion, cantidad);

        else if (tipo == "dinero")
            return new DonacionDinero(descripcion, cantidad);

        return nullptr; // No se encontró tipo
    }
};

#endif
