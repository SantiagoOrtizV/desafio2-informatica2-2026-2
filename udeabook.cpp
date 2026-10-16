#include "udeabook.h"
#include "fecha.h"
#include "usuario.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>

using namespace std;

UdeaBook::UdeaBook(){
    usuarios = nullptr;
    cantidadUsuarios = 0;
    usuarioActual = nullptr;
}

UdeaBook::~UdeaBook() { //libera toda la memoria usada para cargar los usuarios
    delete[] usuarios;
}

unsigned int contarUsuarios(const string ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "Buscando archivos en: " << filesystem::current_path() << endl;
        return 0;
    }
    unsigned int cantidad = 0;
    string linea;

    while (getline(archivo, linea)) {
        cantidad++;
    }
    archivo.close();
    return cantidad;
}

void separarCampos(const string& linea, string campos[5]) {
    unsigned int campo = 0;

    for (unsigned int i = 0;
         i < linea.length() && campo < 5;
         i++) {

        if (linea[i] == ';') {
            campo++;
        } else {
            campos[campo] += linea[i];
        }
    }
}

void UdeaBook::cargaUsuarios(){
    const string ruta = "usuarios.txt";
    cantidadUsuarios = contarUsuarios(ruta);
    ifstream archivo(ruta);
    string linea;

    delete[] usuarios;
    usuarios = nullptr;
    usuarioActual = nullptr;

    usuarios = new Usuario[cantidadUsuarios];

    unsigned int cont = 1;
    while (getline(archivo, linea)) {
        string campos[5];
        if (linea.length() > 0) {
            separarCampos(linea, campos);
        }
        unsigned char valorChar = static_cast<unsigned char>(stoi(campos[3]));
        *(usuarios+cont-1) = Usuario(campos[1], campos[2], campos[4], valorChar, Fecha(campos[0]),cont);
        cont++;
    }
    archivo.close();
}

unsigned int UdeaBook::buscarUsuario(const string usuario){
    unsigned int cont = 0;
    while((cont<cantidadUsuarios)&&(usuario!=(usuarios[cont].getNombre()))){
        cont++;
    }
    cont++;
    if(cont>cantidadUsuarios){
        cont = 0;
    }
    return cont;
}

bool UdeaBook::iniciarSesion(const string& nombre, const string&claveInput){
    unsigned int indiceAux = buscarUsuario(nombre);
    if(indiceAux == 0){
        return false;
    }
    string clave = usuarios[indiceAux-1].getClave();
    if(clave != claveInput){
        return false;
    }
    usuarioActual = usuarios+indiceAux-1;
    return true;
}