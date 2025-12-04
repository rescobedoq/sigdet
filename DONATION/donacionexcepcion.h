#ifndef DONATION_EXCEPTIONS_H
#define DONATION_EXCEPTIONS_H

#include <stdexcept>
#include <string>

// Donante inválido
class DonanteInvalidoException : public std::runtime_error {
public:
    DonanteInvalidoException(const std::string& msg)
        : std::runtime_error("Donante inválido: " + msg) {}
};

// Donación inválida
class DonacionInvalidaException : public std::runtime_error {
public:
    DonacionInvalidaException(const std::string& msg)
        : std::runtime_error("Donación inválida: " + msg) {}
};

// Error en el inventario
class InventarioException : public std::runtime_error {
public:
    InventarioException(const std::string& msg)
        : std::runtime_error("Inventario error: " + msg) {}
};

// Tipo de donación desconocido (Factory Method)
class TipoDonacionDesconocidoException : public std::runtime_error {
public:
    TipoDonacionDesconocidoException(const std::string& tipo)
        : std::runtime_error("Tipo de donación desconocido: " + tipo) {}
};

#endif
