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
    void cargaAlbumes();
    void cargaFotos();

    bool guardarAlbumes() const;
    bool guardarFotos() const;
    bool guardarDatos() const;

    bool iniciarSesion(const string&, const string&);
    unsigned int buscarUsuario(const string);

    //getters para tener acceso al puntero del usuario que inicio sesion
    Usuario* getUsuarioActual();
    const Usuario* getUsuarioActual() const; //lo mismo pero solo modo lectura

    UdeaBook(const UdeaBook&) = delete; //esto evita que se copie por error udeabook ya que sería peligroso por administrar memoria dinamica
    UdeaBook& operator=(const UdeaBook&) = delete;

    ~UdeaBook();
};

#endif
