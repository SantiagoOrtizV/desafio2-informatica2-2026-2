#ifndef USUARIO_H
#define USUARIO_H
#include "fecha.h"
#include <string>

using namespace std;

class Usuario
{
private:
    string nombre;
    string clave;
    string ciudad;
    unsigned char numeroPais;
    Fecha fechaInscripcion;
    unsigned int indiceUsuario;

public:
    Usuario();
    Usuario(string, string, string, unsigned char, Fecha, unsigned int);
    string getNombre();
    string getClave();
    string getCiudad();
    unsigned char getPais();
    Fecha getFecha();
    unsigned int getIndice();
};

#endif // USUARIO_H
