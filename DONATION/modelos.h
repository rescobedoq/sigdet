#ifndef MODELOS_H
#define MODELOS_H

#include <QString>
#include <iostream>

// Clase Abstracta (Polimorfismo puro)
class DonacionBase {
protected:
    QString donante;
    QString producto;
    int cantidad;

public:
    DonacionBase(QString d, QString p, int c) : donante(d), producto(p), cantidad(c) {}
    virtual ~DonacionBase() = default; // Destructor virtual esencial

    // Método virtual puro
    virtual QString getTipo() const = 0;

    // Getters
    QString getDonante() const { return donante; }
    QString getProducto() const { return producto; }
    int getCantidad() const { return cantidad; }
};

// Clase Derivada 1
class Alimento : public DonacionBase {
public:
    Alimento(QString d, QString p, int c) : DonacionBase(d, p, c) {}
    QString getTipo() const override { return "Alimento"; }
};

// Clase Derivada 2
class Ropa : public DonacionBase {
public:
    Ropa(QString d, QString p, int c) : DonacionBase(d, p, c) {}
    QString getTipo() const override { return "Ropa"; }
};

#endif // MODELOS_H
