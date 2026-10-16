#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include "foto.h"
#include "lista.h"
using namespace std;

class Album{
private:
    string nameAlbum;
    unsigned int indicePropietario; //relacionar esto con los usuarios de UdeABook
                                    //los indices de los usuarios se relacionan desde NUMERO 1, no desde 0
    unsigned char privacidad;
    Lista<Foto*> fotos;

public:
    static const unsigned char PUBLICO = 0; //estados para la privacidad del album
    static const unsigned char PRIVADO = 1;
    static const unsigned char AMIGOS = 2;

    Album();
    Album(string nombre, unsigned int indicePropietario, unsigned char privacidad);
    Album(const Album& otro);
    Album& operator=(const Album& otro);

    ~Album();

    //gestionar las fotos
    void agregarFoto(Foto* foto);

    Foto* obtenerFoto(unsigned int indice); //para el dueño del album
    const Foto* obtenerFoto(unsigned int indice) const; //solo lectura para otros usuarios no dueños del album
    unsigned int cantidadFotos() const;


    string getNombre() const;
    unsigned int getIndicePropietario() const;
    unsigned char getPrivacidad() const;

    void setNombre(string nombre);
    void setPrivacidad(unsigned char privacidad);
};

#endif // ALBUM_H
