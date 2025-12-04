#ifndef DONACIONHIGIENE_H
#define DONACIONHIGIENE_H

#include "donacion.h"

class DonacionHigiene : public Donacion {
private:
    std::string producto; // jabón, shampoo, detergente...
    int cantidad;

public:
    DonacionHigiene(const std::string& fecha,
                    const std::string& donante,
                    const std::string& producto,
                    int cantidad);

    std::string info() const override;
};

#endif
