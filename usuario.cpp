#include "usuario.h"

Usuario::Usuario() {
    nombre = "0";
    clave = "0";
    ciudad = "0";
    numeroPais = '0';
    indiceUsuario = 0;
}

Usuario::Usuario(string n, string cl, string ciu, unsigned char nP,
                 Fecha fI, unsigned int iU) {
    nombre = n;
    clave = cl;
    ciudad = ciu;
    numeroPais = nP;
    fechaInscripcion = fI;
    indiceUsuario = iU;
}

string Usuario::getNombre(){
    return nombre;
}

string Usuario::getClave(){
    return clave;
}

string Usuario::getCiudad(){
    return ciudad;
}

unsigned char Usuario::getPais(){
    return numeroPais;
}

Fecha Usuario::getFecha(){
    return fechaInscripcion;
}

unsigned int Usuario::getIndice(){
    return indiceUsuario;
}