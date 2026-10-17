#include "funciones.h"
#include "udeabook.h"
#include <iostream>

int main()
{

    UdeaBook sistema;

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
    return 0;

    /* MENU DE SANTI

    bool salirPrograma, salirInicio;
    UdeaBook sistema;
    salirPrograma = inicio();
    while(!salirPrograma){
        salirInicio = inicio_sesion(sistema);
        salirInicio =! salirInicio;
        if (!salirInicio){
            cout << "Inicio Correcto" << endl;
        }
        salirPrograma = inicio();
    }
*/
}
