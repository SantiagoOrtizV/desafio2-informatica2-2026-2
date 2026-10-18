
#include "mensaje.h"
#include <iostream>

using namespace std;

Mensaje::Mensaje()
    : indiceEmisor(0),
    indiceReceptor(0),
    texto(""),
    fechaEnvio(),
    leido(false) {
}

Mensaje::Mensaje(unsigned int emisor, unsigned int receptor,
                 const string& contenido, const Fecha& fecha)
    : indiceEmisor(emisor),
    indiceReceptor(receptor),
    texto(contenido),
    fechaEnvio(fecha),
    leido(false) {
}

Mensaje::Mensaje(const Mensaje& otro)
    : indiceEmisor(otro.indiceEmisor),
    indiceReceptor(otro.indiceReceptor),
    texto(otro.texto),
    fechaEnvio(otro.fechaEnvio),
    leido(otro.leido) {
}

Mensaje& Mensaje::operator=(const Mensaje& otro) {
    if (this != &otro) {
        indiceEmisor = otro.indiceEmisor;
        indiceReceptor = otro.indiceReceptor;
        texto = otro.texto;
        fechaEnvio = otro.fechaEnvio;
        leido = otro.leido;
    }

    return *this;
}

Mensaje::~Mensaje() {
}

unsigned int Mensaje::getIndiceEmisor() const {
    return indiceEmisor;
}

unsigned int Mensaje::getIndiceReceptor() const {
    return indiceReceptor;
}

const string& Mensaje::getTexto() const {
    return texto;
}

const Fecha& Mensaje::getFechaEnvio() const {
    return fechaEnvio;
}

bool Mensaje::estaLeido() const {
    return leido;
}

void Mensaje::marcarComoLeido() {
    leido = true;
}

bool Mensaje::esValido() const {
    return indiceEmisor != 0
           && indiceReceptor != 0
           && indiceEmisor != indiceReceptor
           && !texto.empty()
           && fechaEnvio.esValida();
}

void Mensaje::mostrar() const {
    cout << "Emisor: " << indiceEmisor << endl;
    cout << "Receptor: " << indiceReceptor << endl;
    cout << "Mensaje: " << texto << endl;

    cout << "Fecha de envio: "
         << fechaEnvio.getDia() << "/"
         << fechaEnvio.getMes() << "/"
         << fechaEnvio.getAnio() << endl;

    cout << "Estado: " << (leido ? "Leido" : "No leido")
         << endl;
}

unsigned long int Mensaje::memoriaUsada() const {
    return sizeof(*this) + texto.capacity() * sizeof(char); //sizeof(*tihs) nos da la cantidad de
                                                            //bytes del objeto mensaje

    //texto.capacity() -> cuantas char puede almacenar la cadena sin necesitar mas memoria
}
