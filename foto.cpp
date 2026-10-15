#include "foto.h"


Foto::Foto() {
    fechaCap = Fecha();
    tamano = 0;
    nombreArchivo = "";
    likes = 0;
}

Foto::Foto(Fecha fecha, unsigned long long tam, string nombre, unsigned int cantLikes) {
    fechaCap = fecha;
    tamano = tam;
    nombreArchivo = nombre;
    likes = cantLikes;
}

Foto::Foto(const Foto& otra) {
    fechaCap = otra.fechaCap;
    tamano = otra.tamano;
    nombreArchivo = otra.nombreArchivo;
    likes = otra.likes;
}

Foto::~Foto() {
}

Foto& Foto::operator=(const Foto& otra) {
    if (this != &otra) {
        fechaCap = otra.fechaCap;
        tamano = otra.tamano;
        nombreArchivo = otra.nombreArchivo;
        likes = otra.likes;
    }

    return *this;
}

Fecha Foto::getFechaCap() const {
    return fechaCap;
}

unsigned long long Foto::getTamano() const {
    return tamano;
}

string Foto::getNombreArchivo() const {
    return nombreArchivo;
}

unsigned int Foto::getLikes() const {
    return likes;
}

void Foto::setFechaCap(Fecha fecha) {
    fechaCap = fecha;
}

void Foto::setTamano(unsigned long long tam) {
    tamano = tam;
}

void Foto::setNombreArchivo(string nombre) {
    nombreArchivo = nombre;
}

void Foto::setLikes(unsigned int cantLikes) {
    likes = cantLikes;
}


