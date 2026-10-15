#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include "lista.h"
#include "foto.h"

using namespace std;

class Album {
private:
    string nameAlbum;
    unsigned int indicePropietario; //relacionar esto con los usuarios de UdeABook
    unsigned char privacidad;
    Lista<Foto*> fotos;

public:
    static const unsigned char PUBLICO = 0;
    static const unsigned char PRIVADO = 1;
    static const unsigned char AMIGOS = 2;

    Album();
    Album(string nombre, unsigned int indicePropietario,
          unsigned char privacidad);

    ~Album();

    void agregarFoto(Foto* foto);

    Foto* obtenerFoto(unsigned int indice);
    const Foto* obtenerFoto(unsigned int indice) const;

    unsigned int cantidadFotos() const;

    string getNombre() const;
    unsigned int getIndicePropietario() const;
    unsigned char getPrivacidad() const;

    void setNombre(string nombre);
    void setPrivacidad(unsigned char privacidad);
};

#endif