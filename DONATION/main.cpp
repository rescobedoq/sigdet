#include <iostream>
#include <memory>
#include <vector>
#include "inventario.h"
#include "donacionfactory.h"

using namespace std;

void mostrarMenu() {
    cout << "\n=== CRUD de Donaciones (Pruebas en Consola) ===\n";
    cout << "1. Registrar donación\n";
    cout << "2. Listar donaciones\n";
    cout << "3. Buscar donación por ID\n";
    cout << "4. Eliminar donación\n";
    cout << "5. Salir\n";
    cout << "Seleccione: ";
}

int main() {
    Inventario inventario;
    DonacionFactory factory;

    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {

        case 1: {
            cout << "\n--- Registrar Donación ---\n";
            cout << "Tipos disponibles:\n";
            cout << "1 = Ropa\n";
            cout << "2 = Alimento\n";
            cout << "3 = Higiene\n";
            cout << "4 = Mueble\n";
            cout << "5 = Libro\n";
            cout << "6 = Equipo Médico\n";
            cout << "7 = Dinero\n";

            int tipo;
            cout << "Tipo: ";
            cin >> tipo;

            cin.ignore(); // limpiar buffer
            string descripcion;
            cout << "Descripción: ";
            getline(cin, descripcion);

            // Crear donación usando Factory Method
            shared_ptr<DonacionBase> d = factory.crearDonacion(tipo, descripcion);

            if (!d) {
                cout << "❌ Tipo no válido!\n";
            } else {
                inventario.agregarDonacion(d);
                cout << "✔ Donación registrada correctamente.\n";
            }
            break;
        }

        case 2: {
            cout << "\n--- Listado de Donaciones ---\n";
            inventario.listarDonaciones();
            break;
        }

        case 3: {
            cout << "\nID a buscar: ";
            int id;
            cin >> id;

            auto don = inventario.buscarDonacion(id);
            if (don)
                don->mostrar();
            else
                cout << "❌ Donación no encontrada\n";
            break;
        }

        case 4: {
            cout << "\nID a eliminar: ";
            int id;
            cin >> id;

            if (inventario.eliminarDonacion(id))
                cout << "✔ Eliminado\n";
            else
                cout << "❌ No encontrado\n";

            break;
        }

        case 5:
            cout << "Saliendo...\n";
            break;

        default:
            cout << "Opción inválida!\n";
        }

    } while (opcion != 5);

    return 0;
}
