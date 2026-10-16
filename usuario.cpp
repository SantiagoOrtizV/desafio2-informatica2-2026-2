#include "usuario.h"
#include "album.h"

Usuario::Usuario()
    : nombre("0"),
    clave("0"),
    ciudad("0"),
    numeroPais(0),
    fechaInscripcion(),
    indiceUsuario(0),
    albumes() {
}

Usuario::Usuario(string n, string cl, string ciu, unsigned char nP, const Fecha& fI, unsigned int iU):
    nombre(n),
    clave(cl),
    ciudad(ciu),
    numeroPais(nP),
    fechaInscripcion(fI),
    indiceUsuario(iU),
    albumes() {
}

// Constructor de copia
Usuario::Usuario(const Usuario& otro)
    : nombre(otro.nombre),
    clave(otro.clave),
    ciudad(otro.ciudad),
    numeroPais(otro.numeroPais),
    fechaInscripcion(otro.fechaInscripcion),
    indiceUsuario(otro.indiceUsuario),
    albumes() { //se iniciliza album como una lista vacia

    for (unsigned int i = 0; i < otro.albumes.tamano(); i++) { //recorremos albumes del usuario original
        if (otro.albumes[i] != nullptr) {
            Album* copia = new Album(*otro.albumes[i]); //creamos un album nuevo y guardamos el puntero a ese nuevo album
            albumes.agregar(copia);
        }
    }
}

// Operador de asignación
Usuario& Usuario::operator=(const Usuario& otro) {
    if (this != &otro) { //asigna tambien al ususario un album debidamente copiado

        // Liberar los álbumes que ya pertenecen a este usuario.
        for (unsigned int i = 0; i < albumes.tamano(); i++) {
            delete albumes[i];
        }

        // Vaciar la lista de punteros.
        albumes = Lista<Album*>();

        // Copiar los atributos sencillos.
        nombre = otro.nombre;
        clave = otro.clave;
        ciudad = otro.ciudad;
        numeroPais = otro.numeroPais;
        fechaInscripcion = otro.fechaInscripcion;
        indiceUsuario = otro.indiceUsuario;

        // Crear copias independientes de los álbumes.
        for (unsigned int i = 0; i < otro.albumes.tamano(); i++) {
            if (otro.albumes[i] != nullptr) {
                Album* copia = new Album(*otro.albumes[i]);
                albumes.agregar(copia);
            }
        }
    }

    return *this;
}

// Destructor
Usuario::~Usuario() {
    for (unsigned int i = 0; i < albumes.tamano(); i++) {
        delete albumes[i]; //debe liberarse así porque albumes es un objeto de tipo Lista<Album*>, no un simple puntero a una lista
                            //liberamos objetos album a los que apunta
    }
}


string Usuario::getNombre() const{
    return nombre;
}

string Usuario::getClave() const{
    return clave;
}

string Usuario::getCiudad() const{
    return ciudad;
}

unsigned char Usuario::getPais() const{
    return numeroPais;
}

const Fecha& Usuario::getFecha() const{
    return fechaInscripcion;
}

unsigned int Usuario::getIndice() const{
    return indiceUsuario;
}

// ---------- Setters ----------

void Usuario::setNombre(const string& n) {
    nombre = n;
}

void Usuario::setClave(const string& cl) {
    clave = cl;
}

void Usuario::setCiudad(const string& ciu) {
    ciudad = ciu;
}

void Usuario::setPais(unsigned char nP) {
    numeroPais = nP;
}

void Usuario::setFecha(const Fecha& fI) {
    fechaInscripcion = fI;
}

void Usuario::setIndice(unsigned int iU) {
    indiceUsuario = iU;
}

//metodos para relacionar usuario con sus albumes
void Usuario::agregarAlbum(Album* album) {
    if (album == nullptr) {
        return;
    }

    for (unsigned int i = 0; i < albumes.tamano(); i++) {
        if (albumes[i] == album) {
            return;
        }
    }

    albumes.agregar(album);
}

Album* Usuario::obtenerAlbum(unsigned int indice) {
    if (indice >= albumes.tamano()) {
        return nullptr;
    }

    return albumes[indice];
}

const Album* Usuario::obtenerAlbum(unsigned int indice) const {
    if (indice >= albumes.tamano()) {
        return nullptr;
    }

    return albumes[indice];
}

unsigned int Usuario::cantidadAlbumes() const {
    return albumes.tamano();
}