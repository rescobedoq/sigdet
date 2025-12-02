#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "modelos.h"
#include "factory.h"
#include <vector>
#include <memory>
#include <future> // Para multithreading
#include <thread>
#include <QDebug>

// Template / Genérico (POO Avanzada): Un repositorio simple
template <typename T>
class Repositorio {
    std::vector<std::shared_ptr<T>> elementos;
public:
    void agregar(std::shared_ptr<T> item) {
        elementos.push_back(item);
    }
    const std::vector<std::shared_ptr<T>>& obtenerTodos() const {
        return elementos;
    }
};

// Controlador (Actúa como Facade/Singleton para la Vista)
class ControladorDonaciones {
private:
    Repositorio<DonacionBase> repositorio;

public:
    ControladorDonaciones() {}

    // Método para registrar usando el Factory
    void registrarDonacion(QString donante, QString producto, int cantidad, bool esRopa) {
        try {
            TipoDonacion tipo = esRopa ? TipoDonacion::ROPA : TipoDonacion::ALIMENTO;

            // Crear usando Factory y mover al repositorio
            auto nuevaDonacion = DonacionFactory::crearDonacion(tipo, donante, producto, cantidad);
            repositorio.agregar(std::move(nuevaDonacion));

        } catch (const std::exception& e) {
            qDebug() << "Error al registrar: " << e.what();
            throw; // Re-lanzar para que la UI lo maneje
        }
    }

    // Multithreading básico: Simula guardar en base de datos en segundo plano
    void guardarEnBaseDeDatosAsync() {
        // Lambda y std::async (Programación Moderna)
        std::thread([=]() {
            // Simular tarea pesada
            std::this_thread::sleep_for(std::chrono::seconds(2));
            qDebug() << "Datos guardados en segundo plano correctamente.";
        }).detach();
    }
};

#endif // CONTROLADOR_H
