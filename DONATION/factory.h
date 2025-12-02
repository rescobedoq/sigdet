#ifndef FACTORY_H
#define FACTORY_H

#include "modelos.h"
#include <memory> // Para smart pointers
#include <stdexcept> // Para manejo de errores

enum class TipoDonacion { ALIMENTO, ROPA };

class DonacionFactory {
public:
    // Uso de std::unique_ptr (Punteros Inteligentes - POO Avanzada)
    static std::unique_ptr<DonacionBase> crearDonacion(TipoDonacion tipo, QString d, QString p, int c) {
        switch (tipo) {
        case TipoDonacion::ALIMENTO:
            return std::make_unique<Alimento>(d, p, c);
        case TipoDonacion::ROPA:
            return std::make_unique<Ropa>(d, p, c);
        default:
            // Manejo de Excepciones (POO Avanzada)
            throw std::invalid_argument("Tipo de donación desconocido");
        }
    }
};

#endif // FACTORY_H
