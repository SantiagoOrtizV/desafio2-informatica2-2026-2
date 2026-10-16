
#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "fecha.h"

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

    Usuario(string n, string cl, string ciu, unsigned char nP, const Fecha& fI, unsigned int iU); //constructor miembro a miembro

    Usuario(const Usuario& otro);

    Usuario& operator=(const Usuario& otro);

    ~Usuario();

    //Getters const para solo consultar
    string getNombre() const;
    string getClave() const;
    string getCiudad() const;
    unsigned char getPais() const;
    Fecha getFecha() const;
    unsigned int getIndice() const;

    //Setters
    void setNombre(const string& n);
    void setClave(const string& cl);
    void setCiudad(const string& ciu);
    void setPais(unsigned char nP);
    void setFecha(const Fecha& fI);
    void setIndice(unsigned int iU);
};

#endif