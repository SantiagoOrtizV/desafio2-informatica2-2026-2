#ifndef MENSAJE_H
#define MENSAJE_H

#include <string>
#include "fecha.h"

using namespace std;

class Mensaje {
private:
    unsigned int indiceEmisor;
    unsigned int indiceReceptor;
    string texto;
    Fecha fechaEnvio;
    bool leido;

public:
    Mensaje();
    Mensaje(unsigned int emisor, unsigned int receptor,
            const string& texto, const Fecha& fechaEnvio);

    Mensaje(const Mensaje& otro);
    Mensaje& operator=(const Mensaje& otro);
    ~Mensaje();

    unsigned int getIndiceEmisor() const;
    unsigned int getIndiceReceptor() const;
    const string& getTexto() const;
    const Fecha& getFechaEnvio() const;
    bool estaLeido() const;

    void marcarComoLeido();

    bool esValido() const;
    void mostrar() const;
    unsigned long int memoriaUsada() const;
};

#endif
