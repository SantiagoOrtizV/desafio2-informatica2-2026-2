#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "fecha.h"
#include "lista.h"

using namespace std;

class Album; //declaracion adelantada, es una clase pero aún no se conocen atributos ni metodos
class Mensaje; //declaracion adelantada, es una clase pero aún no se conocen atributos ni metodos

class Usuario {
private:
    string nombre;
    string clave;
    string ciudad;
    unsigned char numeroPais;
    Fecha fechaInscripcion;
    unsigned int indiceUsuario;
    Lista<Album*> albumes; //cada usuario es dueño de sus albumes (puntero a objetos album)

    Lista<Mensaje*> enviados;
    Lista<Mensaje*> recibidos;

public:
    Usuario();

    Usuario(string n, string cl, string ciu, unsigned char nP, const Fecha& fI, unsigned int iU); //constructor miembro a miembro

    Usuario(const Usuario& otro);

    Usuario& operator=(const Usuario& otro);

    ~Usuario();

    void agregarAlbum(Album* album);
    bool existeAlbum(const string& nombre) const;

    Album* obtenerAlbum(unsigned int indice);
    const Album* obtenerAlbum(unsigned int indice) const;

    unsigned int cantidadAlbumes() const;


    // Metodos para gestionar mensajes
    bool registrarEnviado(Mensaje* mensaje);
    bool registrarRecibido(Mensaje* mensaje);

    bool retirarUltimoEnviado(Mensaje* mensaje);
    bool retirarUltimoRecibido(Mensaje* mensaje);

    unsigned int cantidadEnviados() const;
    unsigned int cantidadRecibidos() const;

    Mensaje* obtenerEnviado(unsigned int indice);
    const Mensaje* obtenerEnviado(unsigned int indice) const;

    Mensaje* obtenerRecibido(unsigned int indice);
    const Mensaje* obtenerRecibido(unsigned int indice) const;


    //Getters const para solo consultar
    string getNombre() const;
    string getClave() const;
    string getCiudad() const;
    unsigned char getPais() const;
    const Fecha& getFecha() const;
    unsigned int getIndice() const;

    //Setters
    void setNombre(const string& n);
    void setClave(const string& cl);
    void setCiudad(const string& ciu);
    void setPais(unsigned char nP);
    void setFecha(const Fecha& fI);
    void setIndice(unsigned int iU);

    unsigned long int memoriaUsada() const;
};

#endif