#include "album.h"
// Constructor por defecto
Album::Album()
    : nameAlbum(""),
    indicePropietario(0),
    privacidad(PRIVADO),
    fotos() {
}

// Constructor con parámetros
Album::Album(string nombre, unsigned int indicePropietario,
             unsigned char privacidad)
    : nameAlbum(nombre),
    indicePropietario(indicePropietario),
    privacidad(PRIVADO),
    fotos() {

    setPrivacidad(privacidad);
}

// Destructor
Album::~Album() {       //cada posicion de fotos contiene un puntero a un objeto Foto, este ciclo destruye cada OBJETO, luego se desturye
                    //el atributo fotos y el destructor de Lista libera ese arreglo de punteros
    for (unsigned int i = 0; i < fotos.tamano(); i++) {
        delete fotos[i];
    }
}

// Agregar una foto
void Album::agregarFoto(Foto* foto) {
    if (foto == nullptr) {
        return;
    }

    // Evitar registrar dos veces el mismo puntero
    for (unsigned int i = 0; i < fotos.tamano(); i++) {
        if (fotos[i] == foto) {
            return;
        }
    }

    fotos.agregar(foto);
}

// Obtener una foto por índice
Foto* Album::obtenerFoto(unsigned int indice) {
    if (indice >= fotos.tamano()) {
        return nullptr;
    }

    return fotos[indice];
}

// Obtener una foto de solo lectura
const Foto* Album::obtenerFoto(unsigned int indice) const {
    if (indice >= fotos.tamano()) {
        return nullptr;
    }

    return fotos[indice];
}

// Cantidad de fotos
unsigned int Album::cantidadFotos() const {
    return fotos.tamano();
}

// Getters
string Album::getNombre() const {
    return nameAlbum;
}

unsigned int Album::getIndicePropietario() const {
    return indicePropietario;
}

unsigned char Album::getPrivacidad() const {
    return privacidad;
}

// Setters
void Album::setNombre(string nombre) {
    this->nameAlbum = nombre;
}

void Album::setPrivacidad(unsigned char privacidad) {
    if (privacidad == PUBLICO ||
        privacidad == PRIVADO ||
        privacidad == AMIGOS) {
        this->privacidad = privacidad;
    }
}