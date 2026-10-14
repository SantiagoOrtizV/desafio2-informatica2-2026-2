#ifndef UDEABOOK_H
#define UDEABOOK_H
#include "usuario.h"
#include <string>

using namespace std;

class UdeaBook
{
private:
    Usuario* usuarios;
    unsigned int cantidadUsuarios;
    Usuario* usuarioActual;

public:
    UdeaBook();
    void cargaUsuarios();
    bool iniciarSesion(const string&, const string&);
    unsigned int buscarUsuario(const string);
};

#endif
