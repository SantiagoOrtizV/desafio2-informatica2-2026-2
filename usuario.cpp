#include "usuario.h"
#include "album.h"
#include "mensaje.h"

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
    albumes(),
    enviados(), //no copiamos los mensajes porque dos objetos Usuario pueden quedar apuntando
                //a un mismo objeto mensaje creyendo que son propietarios
    recibidos()
{
    for (unsigned int i = 0; i < otro.albumes.tamano(); i++) {
        if (otro.albumes[i] != nullptr) {
            albumes.agregar(new Album(*otro.albumes[i]));
        }
    }
}

// Operador de asignación
Usuario& Usuario::operator=(const Usuario& otro) {
    if (this != &otro) {
        // Liberar los albumes actuales
        for (unsigned int i = 0; i < albumes.tamano(); i++) {
            delete albumes[i];
        }

        // Liberar los mensajes recibidos actuales
        for (unsigned int i = 0; i < recibidos.tamano(); i++) {
            delete recibidos[i];
        }

        // Las listas de punteros no propietarios se limpian sin borrar
        // los objetos a los que apuntan
        albumes = Lista<Album*>();
        enviados = Lista<Mensaje*>();
        recibidos = Lista<Mensaje*>();

        // Copiar los atributos basicos
        nombre = otro.nombre;
        clave = otro.clave;
        ciudad = otro.ciudad;
        numeroPais = otro.numeroPais;
        fechaInscripcion = otro.fechaInscripcion;
        indiceUsuario = otro.indiceUsuario;

        // Copiar profundamente los albumes
        for (unsigned int i = 0; i < otro.albumes.tamano(); i++) {
            if (otro.albumes[i] != nullptr) {
                albumes.agregar(new Album(*otro.albumes[i]));
            }
        }
    }

    return *this;
}

// Destructor

Usuario::~Usuario() {
    // El usuario es propietario de sus albumes
    for (unsigned int i = 0; i < albumes.tamano(); i++) { //debe liberarse así porque albumes es un objeto de tipo Lista<Album*>
    //no un simple puntero a una lista, liberamos objetos album a los que apunta
        delete albumes[i];
    }

    // El usuario receptor es propietario de sus mensajes recibidos
    for (unsigned int i = 0; i < recibidos.tamano(); i++) {
        delete recibidos[i];
    }
    //no borramos mensjaes enviados, pertencen al receptor
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

bool Usuario::existeAlbum(const string& nombre) const {
    for (unsigned int i = 0; i < albumes.tamano(); i++) {
        if (albumes[i] != nullptr &&
            albumes[i]->getNombre() == nombre) {
            return true;
        }
    }

    return false;
}

bool Usuario::registrarEnviado(Mensaje* mensaje) {
    if (mensaje == nullptr) {
        return false;
    }

    for (unsigned int i = 0; i < enviados.tamano(); i++) {
        if (enviados[i] == mensaje) {
            return false;
        }
    }

    enviados.agregar(mensaje);
    return true;
}

bool Usuario::registrarRecibido(Mensaje* mensaje) {
    if (mensaje == nullptr) {
        return false;
    }

    for (unsigned int i = 0; i < recibidos.tamano(); i++) {
        if (recibidos[i] == mensaje) {
            return false;
        }
    }

    recibidos.agregar(mensaje);
    return true;
}

bool Usuario::retirarUltimoEnviado(Mensaje* mensaje) { //Compara el último puntero antes de retirarlo
    //para evitar eliminar accidentalmente otro registro
    unsigned int cantidad = enviados.tamano();

    if (cantidad == 0 || enviados[cantidad - 1] != mensaje) {
        return false;
    }

    return enviados.quitarUltimo();
}

bool Usuario::retirarUltimoRecibido(Mensaje* mensaje) { //Compara el último puntero antes de retirarlo
    //para evitar eliminar accidentalmente otro registro
    unsigned int cantidad = recibidos.tamano();

    if (cantidad == 0 || recibidos[cantidad - 1] != mensaje) {
        return false;
    }

    return recibidos.quitarUltimo();
}


unsigned int Usuario::cantidadEnviados() const {
    return enviados.tamano();
}

unsigned int Usuario::cantidadRecibidos() const {
    return recibidos.tamano();
}

Mensaje* Usuario::obtenerEnviado(unsigned int indice) {
    if (indice >= enviados.tamano()) {
        return nullptr;
    }

    return enviados[indice];
}

const Mensaje* Usuario::obtenerEnviado(unsigned int indice) const {
    if (indice >= enviados.tamano()) {
        return nullptr;
    }

    return enviados[indice];
}

Mensaje* Usuario::obtenerRecibido(unsigned int indice) {
    if (indice >= recibidos.tamano()) {
        return nullptr;
    }

    return recibidos[indice];
}

const Mensaje* Usuario::obtenerRecibido(unsigned int indice) const {
    if (indice >= recibidos.tamano()) {
        return nullptr;
    }

    return recibidos[indice];
}