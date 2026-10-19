#ifndef FOTO_H
#define FOTO_H

#include <string>
#include "fecha.h"

using namespace std;

class Foto {
private:
    Fecha fechaCap;
    unsigned long long tamano;
    string nombreArchivo;
    unsigned int likes;

public:
//constructores
    Foto();
    Foto(Fecha fCap, unsigned long long tam, string ruta, unsigned int cantLikes);
    Foto(const Foto& nuevaFecha);
    ~Foto();

    //operador = para fotos
    Foto& operator=(const Foto& otra);


//Getters
    const Fecha& getFechaCap() const;
    unsigned long long getTamano() const;
    string getNombreArchivo() const;
    unsigned int getLikes() const;

//Setters
    void setFechaCap(Fecha fechaCap);
    void setTamano(unsigned long long tam);
    void setNombreArchivo(string nombre);
    void setLikes(unsigned int cantLikes);

    unsigned long int memoriaUsada() const;
};

#endif // FOTO_H
