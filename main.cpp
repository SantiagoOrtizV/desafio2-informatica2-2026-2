#include "funciones.h"

int main()
{
    bool salir = false;
    bool inicio_valido;
    while(!salir){
        inicio_valido = inicio_sesion(salir);
        menu(inicio_valido);
    }
}
