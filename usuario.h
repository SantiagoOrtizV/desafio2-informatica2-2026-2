#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "fecha.h"
#include "lista.h"

using namespace std;

class Album; //declaracion adelantada, es una clase pero aún no se conocen atributos ni metodos

class Usuario {
private:
    string nombre;
    string clave;
    string ciudad;
    unsigned char numeroPais;
    Fecha fechaInscripcion;
    unsigned int indiceUsuario;
    Lista<Album*> albumes; //cada usuario es dueño de sus albumes (puntero a objetos album)

public:
    Usuario();

    Usuario(string n, string cl, string ciu, unsigned char nP, const Fecha& fI, unsigned int iU); //constructor miembro a miembro

    Usuario(const Usuario& otro);

    Usuario& operator=(const Usuario& otro);

    ~Usuario();

    void agregarAlbum(Album* album);

    Album* obtenerAlbum(unsigned int indice);
    const Album* obtenerAlbum(unsigned int indice) const;

    unsigned int cantidadAlbumes() const;

    //Getters const para solo consultar
    string getNombre() const;
    string getClave() const;
    string getCiudad() const;
    unsigned char getPais() const;
    const Fecha& getFecha() const;
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