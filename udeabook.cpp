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
    string campos[5];
    usuarios = new Usuario[cantidadUsuarios];
    unsigned int cont = 1;
    while (getline(archivo, linea)) {
        if (linea.length() > 0) {
            separarCampos(linea, campos);
        }
        unsigned char valorChar = static_cast<unsigned char>(stoi(campos[3]));
        *(usuarios+cont) = Usuario(campos[0], campos[1], campos[2], valorChar, Fecha(campos[4]), cont);
        cont++;
    }
    archivo.close();
}

unsigned int UdeaBook::buscarUsuario(const string usuario){
    unsigned int cont = 0;
    while(usuario!=(usuarios[cont].getNombre())&&(cont<cantidadUsuarios)){
        cont++;
    }
    return cont+1;
}

bool UdeaBook::iniciarSesion(const string& nombre, const string&claveInput){
    unsigned int indiceAux = buscarUsuario(nombre);
    if(indiceAux == 0){
        return false;
    }
    string clave = usuarios[indiceAux].getClave();
    if(clave != claveInput){
        return false;
    }
    usuarioActual = usuarios+indiceAux-1;
    return true;
}