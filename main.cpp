#include "funciones.h"
#include "udeabook.h"

int main()
{
    bool salirPrograma, salirInicio;
    UdeaBook sistema;
    salirPrograma = inicio();
    while(!salirPrograma){
        salirInicio = inicio_sesion(sistema);
        if (!salirInicio){
            //menu;
        }
        salirPrograma = inicio();
    }
}
