
#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "Fecha.h"

using namespace std;

class Usuario {
private:
    string nombre;
    string clave;
    string ciudad;
    unsigned char numeroPais;
    Fecha fechaInscripcion;
    unsigned int indiceUsuario;

public:
    Usuario();

    Usuario(string n, string cl, string ciu, unsigned char nP, Fecha fI, unsigned int iU);

    Usuario(const Usuario& otro);

    Usuario& operator=(const Usuario& otro);

    ~Usuario();

    //Getters
    string getNombre();
    string getClave();
    string getCiudad();
    unsigned char getPais();
    Fecha getFecha();
    unsigned int getIndice();

    //Setters
    void setNombre(const string& n);
    void setClave(const string& cl);
    void setCiudad(const string& ciu);
    void setPais(unsigned char nP);
    void setFecha(const Fecha& fI);
    void setIndice(unsigned int iU);
};

#endif
