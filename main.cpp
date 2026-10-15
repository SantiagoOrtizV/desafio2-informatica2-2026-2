#include "funciones.h"
#include "udeabook.h"
#include <iostream>

int main()
{
    bool salirPrograma, salirInicio;
    UdeaBook sistema;
    salirPrograma = inicio();
    while(!salirPrograma){
        salirInicio = inicio_sesion(sistema);
        salirInicio =! salirInicio;
        if (!salirInicio){
            cout << "Inicio Correcto" << endl;
            //menu;
        }
        salirPrograma = inicio();
    }
}
