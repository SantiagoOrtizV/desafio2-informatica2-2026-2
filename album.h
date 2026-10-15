#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include "foto.h"
using namespace std;

class Album{
private:
    string nameAlbum;
    unsigned int indexPropietario; //relacionar esto con los indices de los usuarios en UdeABook
    unsigned char privacidad;
    Foto** fotos;
    unsigned int cantidadFotos;

public:
};

#endif // ALBUM_H
