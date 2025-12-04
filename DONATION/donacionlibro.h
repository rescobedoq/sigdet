#ifndef DONACIONLIBRO_H
#define DONACIONLIBRO_H

#include "donacion.h"

class DonacionLibro : public Donacion {
private:
    std::string titulo;
    std::string categoria;

public:
    DonacionLibro(const std::string& fecha,
                  const std::string& donante,
                  const std::string& titulo,
                  const std::string& categoria);

    std::string info() const override;
};

#endif
