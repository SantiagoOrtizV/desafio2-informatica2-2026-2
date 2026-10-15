#include "usuario.h"

Usuario::Usuario() {
    nombre = "0";
    clave = "0";
    ciudad = "0";
    numeroPais = '0';
    indiceUsuario = 0;
}

Usuario::Usuario(string n, string cl, string ciu, unsigned char nP, const Fecha& fI, unsigned int iU) {
    nombre = n;
    clave = cl;
    ciudad = ciu;
    numeroPais = nP;
    fechaInscripcion = fI;
    indiceUsuario = iU;
}

// Constructor de copia
Usuario::Usuario(const Usuario& otro)
    : nombre(otro.nombre),
    clave(otro.clave),
    ciudad(otro.ciudad),
    numeroPais(otro.numeroPais),
    fechaInscripcion(otro.fechaInscripcion),
    indiceUsuario(otro.indiceUsuario) {
}

// Operador de asignación
Usuario& Usuario::operator=(const Usuario& otro) {
    if (this != &otro) {
        nombre = otro.nombre;
        clave = otro.clave;
        ciudad = otro.ciudad;
        numeroPais = otro.numeroPais;
        fechaInscripcion = otro.fechaInscripcion;
        indiceUsuario = otro.indiceUsuario;
    }

    return *this;
}

// Destructor
Usuario::~Usuario() {
}

//getters

string Usuario::getNombre(){
    return nombre;
}

string Usuario::getClave(){
    return clave;
}

string Usuario::getCiudad(){
    return ciudad;
}

unsigned char Usuario::getPais(){
    return numeroPais;
}

Fecha Usuario::getFecha(){
    return fechaInscripcion;
}

unsigned int Usuario::getIndice(){
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