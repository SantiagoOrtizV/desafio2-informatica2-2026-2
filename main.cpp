
#include "funciones.h"
#include "udeabook.h"
#include <iostream>

using namespace std;

int main() {
    UdeaBook sistema;

    // Cargar los datos en el orden correcto.
    sistema.cargaUsuarios();
    sistema.cargaAlbumes();
    sistema.cargaFotos();

    bool salirPrograma = false;

    while (!salirPrograma) {
        salirPrograma = inicio();

        if (salirPrograma) {
            break;
        }

        bool inicioCorrecto = inicio_sesion(sistema);

        if (inicioCorrecto) {
            cout << "Inicio Correcto" << endl;
            menu(sistema);
        }
    }

    // Guardar los cambios antes de terminar
    if (sistema.guardarDatos()) {
        cout << "Datos guardados correctamente." << endl;
    } else {
        cout << "Error al guardar los datos." << endl;
    }

    return 0;
}
